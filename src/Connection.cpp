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

namespace aosnet{
	Connection::Connection()
	{
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

	void Connection::setHost(uint32_t h){host = h;};
	void Connection::setPort(uint32_t p){port = p;};
	void Connection::setVersion(uint32_t v){version = v;};

	bool Connection::connect(uint32_t h, uint32_t p, uint32_t v)
	{ 
		setHost(h);
		setPort(p);
		setVersion(v);
		return false;
	}
	
}