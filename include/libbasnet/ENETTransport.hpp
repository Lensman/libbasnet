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
#ifndef ENET_TRANSPORT_HPP
#define ENET_TRANSPORT_HPP

#include "libbasnet/IConnection.hpp"
#include "libbasnet/ITransport.hpp"
#include "libbasnet/BaseTransport.hpp"
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

namespace aosnet 
{
	namespace Transport 
	{
		namespace ENET {

			class Worker : public IWorker 
			{  

			public:   
				Worker::~Worker();
				Worker(boost::shared_ptr<aosnet::IConnection>);  
				// This gets carried out when worker is not sleeping 
				void payload( fPS cbClose, fPS cbRecv, std::string message );

			};  

 			class Transport : public ITransport, private BaseTransport
			{

			private:
			
				Worker *worker;
				bool working;
				std::string tag;

			public:
				Transport(  fPS onDisconnectCallback, fPS onRecvCallback );
				~Transport(void);

				bool hasFinished(void){return working;}				
				void close(std::string message);
				void recv(std::string message);
				
				void disconnect(void);
				bool connect( boost::shared_ptr<aosnet::IConnection> connection );
			};
		}
	}
}
#endif //ENET_TRANSPORT_HPP