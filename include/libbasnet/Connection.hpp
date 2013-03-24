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
	protected:
		void Connection::setHost(uint32_t);
		void Connection::setPort(uint32_t);
		void Connection::setVersion(uint32_t);
	};
}
#endif // CONNECTION_HPP