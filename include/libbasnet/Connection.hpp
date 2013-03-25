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
		Connection::Connection(uint32_t h, uint32_t p, uint32_t v );
		Connection::~Connection();

		uint32_t getHost(void);
		uint32_t getPort(void);
		uint32_t getVersion(void);
	};
}
#endif // CONNECTION_HPP