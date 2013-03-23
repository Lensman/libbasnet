#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

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
		namespace Dummy {

			class Worker : public IWorker 
			{  

			public:   
				Worker::~Worker();
				Worker();  
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
#endif