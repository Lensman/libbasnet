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
#include "libbasnet/basnet.hpp"
/* 
this is now just a placeholder class
*/
namespace aosnet{
	Connection::Connection( uint32_t h, uint32_t p, uint32_t v ) :
		host(h)
		, port(p)
		, version(v)

	{
		LOG(Log::logDEBUG4)  << "NEW Connection STARTED";
	};
	Connection::~Connection(){
		LOG(Log::logDEBUG4)  << "Connection REMOVED";
	};

	uint32_t Connection::getHost(void){return host;};
	uint32_t Connection::getPort(void){return port;};
	uint32_t Connection::getVersion(void){return version;};
}