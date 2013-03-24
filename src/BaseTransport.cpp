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
#include "libbasnet/BaseTransport.hpp"
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>


namespace aosnet 
{
	namespace Transport 
	{
		IWorker::~IWorker(){};

			void IWorker::work( fPS cbClose, fPS cbRecv ){
				unsigned int cnt =0;
				while(true)
				{
					try
					{
						cnt++;
						payload( cbClose, cbRecv, std::to_string((long double)cnt) );
						//cbRecv(std::to_string((long double)cnt));
						boost::this_thread::sleep(boost::posix_time::milliseconds(100));
						boost::this_thread::yield();
						//if (cnt>n)
						//	throw new boost::thread_interrupted;
						boost::this_thread::interruption_point();
					}
					catch(const boost::thread_interrupted&)
					{
						// Thread interruption request received, break the loop
						cbClose(std::string("Exiting Worker thread."));
						break;
					}
				}
			
			}

			BaseTransport::BaseTransport(void){LOG(Log::logDEBUG)  << "BASE transport STARTED"; }
			BaseTransport::~BaseTransport(void){LOG(Log::logDEBUG)  <<  "BASE transport REMOVED";}
			void BaseTransport::work(uint32_t n){};

			void BaseTransport::startWorker( IWorker *work, fPS cbClose, fPS cbRecv )
			{
				wThread = new boost::thread(&IWorker::work, work
					, cbClose
					, cbRecv
				); 	
			};

			void BaseTransport::cleanUp(){
				if ( wThread ){
					wThread->interrupt();
					delete wThread;
				}
			}
			void BaseTransport::callOnDisconnect(std::string message){
				/* Call the callback*/
				getOnDisconnectCallback()(message);
			}
			void BaseTransport::callOnRecv(std::string message){
				/* Call the callback*/
				getOnRecvCallback()(message);
			}

	}
}