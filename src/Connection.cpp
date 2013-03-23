#include "libbasnet/basnet.hpp"

namespace aosnet{
	Connection::Connection(){
		LOG(Log::logDEBUG4)  << "NEW Connection STARTED";
		port = 1212;
	};
	Connection::~Connection(){
		LOG(Log::logDEBUG4)  << "Connection REMOVED";
	};
	void Connection::onDisconnect(std::string message){
		LOG(Log::logDEBUG4)  << "Connection DISCONNECT " << message << " RECV";
	}
	void Connection::onRecv(std::string message){
		LOG(Log::logDEBUG)  << "Connection RECV " << message;
	}

	void Connection::send(Data * data, uint32_t length){
	}
	uint32_t Connection::getHost(void){return host;};
	uint32_t Connection::getPort(void){return port;};
	uint32_t Connection::getVersion(void){return version;};
	
	bool Connection::connect(uint32_t host, uint32_t port, uint32_t version){ return false; }
	
}