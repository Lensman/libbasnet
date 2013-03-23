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
			Worker::Worker(){LOG(Log::logDEBUG) <<  "NULL worker STARTED"; }  

			// This gets carried out when worker is not sleeping 
			void Worker::payload( fPS cbClose, fPS cbRecv, std::string message ){
				cbRecv(message);
			}

			Transport::Transport(  fPS onDisconnectCallback, fPS onRecvCallback ) : BaseTransport() { 
				
				working = true;
				LOG(Log::logDEBUG) <<  "NULL transport STARTED"; 

				setOnDisconnectCallback(onDisconnectCallback);
				setOnRecvCallback(onRecvCallback);

				//setOnDisconnectCallback(NULL);
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
				LOG(Log::logDEBUG) <<  "NULL transport DELETED"; 
			}

			void Transport::disconnect(void){
				BaseTransport::cleanUp();
				if ( worker ){
					delete worker;
				}
				LOG(Log::logDEBUG) <<  "NULL transport REMOVED"; 
			}
			bool Transport::connect( boost::shared_ptr<aosnet::IConnection> connection ){
				LOG(Log::logDEBUG) << "NULL transport CONNECTED";
				worker = new Worker();
					
				fPS cbClose = boost::bind( &Transport::close, this, _1);
				fPS cbRecv = boost::bind( &Transport::recv, this, _1);
	

				BaseTransport::startWorker(worker, cbClose, cbRecv);

				return true;
			}
		}
	}
}
