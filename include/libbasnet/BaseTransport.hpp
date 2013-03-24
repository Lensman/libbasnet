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
#ifndef BASE_TRANSPORT_HPP
#define BASE_TRANSPORT_HPP
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

#include "libbasnet/types.hpp"

namespace aosnet 
{
	namespace Transport 
	{
		class IWorker  
		{  

		public: 

			virtual void operator()(){}  // three sets
			virtual ~IWorker();
			virtual void payload( fPS cbClose, fPS cbRecv, std::string ){};
			void work( fPS cbClose, fPS cbRecv );
		};

		class BaseTransport {
		private:

			boost::thread *wThread;  
			fPS onRecieve;
			fPS onConnect;
			fPS onDisconnect;
		public:
			BaseTransport(void);
			virtual ~BaseTransport(void);
			virtual void BaseTransport::work(uint32_t n);

			void setOnRecvCallback(fPS callback){onRecieve = callback;}
			fPS getOnRecvCallback(void){return onRecieve;}

			void setOnDisconnectCallback(fPS callback){onDisconnect = callback;}
			fPS getOnDisconnectCallback(void){return onDisconnect;}

			void startWorker( IWorker *work, fPS cbClose, fPS cbRecv );
			void cleanUp();
			void callOnDisconnect(std::string message);
			void callOnRecv(std::string message);

		};
	}
}
#endif BASE_TRANSPORT_HPP