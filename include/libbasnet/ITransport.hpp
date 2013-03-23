#ifndef ITRANSPORT_HPP
#define ITRANSPORT_HPP
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

#include "libbasnet/IConnection.hpp"
namespace aosnet {
	namespace Transport {
		class ITransport 
		{
		private:
			bool working;

		public:

			virtual ~ITransport(void){
			};
			virtual bool connect( boost::shared_ptr<aosnet::IConnection> connection ) = 0;
			virtual void disconnect(void) = 0;
			virtual void send(Data * data, uint32_t length){};
			virtual void work(uint32_t n){};
			virtual bool hasFinished(void) = 0;
			virtual void close(void){};
			virtual void recv(std::string message){};
		};
	}
}

#endif // ITRANSPORT_HPP
