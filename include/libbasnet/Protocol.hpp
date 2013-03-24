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