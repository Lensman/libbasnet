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

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>


namespace aosnet 
{
	typedef boost::function<void(void)> fP;
	typedef boost::function<void(std::string)> fPS;

	namespace Transport 
	{
		namespace Dummy {

			Worker::~Worker(){LOG(Log::logDEBUG) <<  "NULL worker object DELETED";}
			Worker::Worker(boost::shared_ptr<aosnet::IConnection> connection ){LOG(Log::logDEBUG) <<  "NULL worker STARTED"; }  

			// This gets carried out when worker is not sleeping 
			void Worker::payload( fPS cbClose, fPS cbRecv, std::string message )
			{
				cbRecv(message);
			}

			Transport::Transport(  fPS onDisconnectCallback, fPS onRecvCallback ) : BaseTransport() 
			{ 
				working = true;
				LOG(Log::logDEBUG) <<  "NULL transport STARTED"; 

				setOnDisconnectCallback(onDisconnectCallback);
				setOnRecvCallback(onRecvCallback);
			}	

			void Transport::close(std::string message)
			{
				BaseTransport::callOnDisconnect(message);
			}

			void Transport::recv(std::string message)
			{
				BaseTransport::callOnRecv(message);
			}

			Transport::~Transport(void)
			{
				BaseTransport::cleanUp();
				if ( worker ){delete worker;}
				LOG(Log::logDEBUG) <<  "NULL transport DELETED"; 
			}

			void Transport::disconnect(void)
			{
				BaseTransport::cleanUp();
				if ( worker ){
					delete worker;
				}
				LOG(Log::logDEBUG) <<  "NULL transport REMOVED"; 
			}

			bool Transport::connect( boost::shared_ptr<aosnet::IConnection> connection )
			{
				LOG(Log::logDEBUG) << "NULL transport CONNECTED";
				worker = new Worker( connection );
					
				fPS cbClose = boost::bind( &Transport::close, this, _1);
				fPS cbRecv = boost::bind( &Transport::recv, this, _1);
	
				BaseTransport::startWorker(worker, cbClose, cbRecv);
				return true;
			}
		}
	}
}
