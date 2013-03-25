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

		/* These member functions will be called by ITransport */
		virtual uint32_t getHost(void) =0;
		virtual uint32_t getPort(void) =0;
		virtual uint32_t getVersion(void) =0;
	};
}

#endif //ICONNECTION_HPP
