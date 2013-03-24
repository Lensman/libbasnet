/*
Copyright (c) Lensman 2012-2013.

This file is part of libbasnet.

libbasnet is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libbasnet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with libbasnet.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "libbasnet/basnet.hpp"
#include "libbasnet/IConnection.hpp"
#include "libbasnet/ITransport.hpp"
#include "libbasnet/Transport.hpp"
#include <enet/enet.h>

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>


namespace aosnet 
{
	typedef boost::function<void(void)> fP;
	typedef boost::function<void(std::string)> fPS;

	namespace Transport 
	{
		namespace ENET {

			ENetEvent event;
			ENetHost * host=0;
			ENetPeer * peer=0;
			ENetAddress address;

			Worker::~Worker()
			{
				LOG(Log::logDEBUG) <<  "ENET worker object DELETED";
				enet_deinitialize();
			}

			Worker::Worker( boost::shared_ptr<aosnet::IConnection> connection )
			{

				LOG(Log::logDEBUG) <<  "ENET worker STARTING";
			    if (enet_initialize () != 0)
				{
					LOG(Log::logDEBUG) << "An error occurred while initializing ENet.";
				}else{
					LOG(Log::logDEBUG) <<  "ENET worker STARTED";
				}

				    address.port = connection->getPort();
					enet_address_set_host (&address, "10.0.0.2");

					fflush(stdout);

					host = enet_host_create (NULL /* create a client host */,
											 1 /* only allow 1 outgoing connection */,
											 1 /* allow up 2 channels to be used, 0 and 1 */,
											 0,
											 0);
					if (!host)
					{
						LOG(Log::logERROR) << "An error occurred while trying to create an ENet client host.";
						exit (EXIT_FAILURE);
					}

					enet_host_compress_with_range_coder(host);
					peer = enet_host_connect (host, &address, 2, connection->getVersion() );

					peer->data=0; // use this as mark that connection is not yet acknowledged

					if (!peer)
					{
						LOG(Log::logERROR) << "No available peers for initiating an ENet connection.";
					}
			}  

			// This gets carried out when worker is not sleeping 
			void Worker::payload( fPS cbClose, fPS cbRecv, std::string message ){

				while (enet_host_service (host, &event, 2500) > 0)
				{
					switch (event.type)
					{
					case ENET_EVENT_TYPE_CONNECT:
					{
						char buf[64];
						sprintf(buf,"%u:%u",event.peer -> address.host, event.peer -> address.port);
						int buflen=strlen(buf);
						event.peer -> data=malloc(buflen+1);
						strncpy((char*)event.peer -> data,buf,buflen);
						peer=event.peer;
						LOG(Log::logDEBUG) << "ENET connection established : "
								<< &event.peer->data;
						break;
					}
					case ENET_EVENT_TYPE_RECEIVE:
					{
						cbRecv( std::string( (char *)event.packet->data, event.packet->dataLength ) );
						break;
					}
					case ENET_EVENT_TYPE_DISCONNECT:
						free(event.peer -> data);
						event.peer -> data = 0; // reset the peer's client information.
						peer=0;
						enet_deinitialize();
						cbClose( std::string("host disconnected.") );
					default:
						break;
					}
				}
			}

			Transport::Transport(  fPS onDisconnectCallback, fPS onRecvCallback ) : BaseTransport() { 
				
				working = true;
				LOG(Log::logDEBUG) <<  "ENET transport STARTED"; 

				setOnDisconnectCallback(onDisconnectCallback);
				setOnRecvCallback(onRecvCallback);
			}	

			void Transport::close(std::string message){
				BaseTransport::callOnDisconnect(message);
			}

			void Transport::recv(std::string message){
				BaseTransport::callOnRecv(message);
			}

			Transport::~Transport(void){
				BaseTransport::cleanUp();
				if ( worker ){delete worker;}
				LOG(Log::logDEBUG) <<  "ENET transport DELETED"; 
			}

			void Transport::disconnect(void){
				BaseTransport::cleanUp();
				if ( worker ){
					delete worker;
				}
				LOG(Log::logDEBUG) <<  "ENET transport REMOVED"; 
			}

			bool Transport::connect( boost::shared_ptr<aosnet::IConnection> connection ){
				LOG(Log::logDEBUG) << "ENET transport CONNECTING";
				worker = new Worker( connection );
					
				fPS cbClose = boost::bind( &Transport::close, this, _1);
				fPS cbRecv = boost::bind( &Transport::recv, this, _1);
	
				BaseTransport::startWorker(worker, cbClose, cbRecv );
				return true;
			}
		}
	}
}
