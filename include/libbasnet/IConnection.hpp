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
		virtual void setHost(uint32_t) =0;
		virtual void setPort(uint32_t) =0;
		virtual void setVersion(uint32_t) =0;
	protected:

	};
}

#endif ICONNECTION_HPP
