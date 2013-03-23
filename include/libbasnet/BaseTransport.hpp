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