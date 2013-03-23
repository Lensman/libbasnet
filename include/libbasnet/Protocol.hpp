#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP
#include "libbasnet/IConnection.hpp"
#include "libbasnet/ITransport.hpp"
#include "stdint.h"


namespace aosnet
{
	typedef boost::shared_ptr<aosnet::IConnection> pConnection;
	typedef boost::shared_ptr<aosnet::Transport::ITransport> pTransport;

    class Protocol
    {
	private:
		uint32_t Protocol::getFirstTransport();
		
		void Protocol::deleteAllTransports(void);
		boost::shared_ptr<aosnet::IConnection> Protocol::getContext();
		boost::shared_ptr<aosnet::Transport::ITransport> Protocol::getTransport( aosnet::Types tranType );
		std::map<std::string, pConnection> connections;
		std::map<std::string, pTransport> transports;

    public:
		void Protocol::deleteTransport( char * tag);
		Protocol::Protocol( char * tag );
		Protocol::~Protocol();
		uint32_t Protocol::getTransportCount();

    };

}


#endif