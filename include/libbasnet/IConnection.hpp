#ifndef ICONNECTION_HPP
#define ICONNECTION_HPP
#include "stdint.h"

#include "libbasnet/types.hpp"

namespace aosnet{
	class IConnection
	{
	public:
		virtual ~IConnection(void){};
		virtual bool connect(uint32_t host, uint32_t port, uint32_t version) = 0;
		virtual uint32_t getHost(void) =0;
		virtual uint32_t getPort(void) =0;
		virtual uint32_t getVersion(void) =0;
		virtual void send(Data * data, uint32_t length) =0;
		/* These member functions will be called by ITransport */
		virtual void onDisconnect(std::string message) =0;
		virtual void onRecv(std::string message) =0;
	};
}

#endif ICONNECTION_HPP
