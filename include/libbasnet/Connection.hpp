#ifndef CONNECTION_HPP
#define CONNECTION_HPP
#include "libbasnet/IConnection.hpp"
#include "stdint.h"

namespace aosnet
{
	class Connection : public IConnection
	{
	private:
		uint32_t host;
		uint32_t port;
		uint32_t version;
		bool isConnected;
	public:
		Connection::Connection();
		Connection::~Connection();

		bool connect(uint32_t host, uint32_t port, uint32_t version );
		void send(Data * data, uint32_t length);
		
		uint32_t getHost(void);
		uint32_t getPort(void);
		uint32_t getVersion(void);
		void onDisconnect(std::string tag);
		void onRecv(std::string message);
	};
}
#endif // CONNECTION_HPP