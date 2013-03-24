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
#ifndef ITRANSPORT_HPP
#define ITRANSPORT_HPP
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>

#include "libbasnet/IConnection.hpp"
namespace aosnet {
	namespace Transport {
		class ITransport 
		{
		private:
			bool working;

		public:

			virtual ~ITransport(void){
			};
			virtual bool connect( boost::shared_ptr<aosnet::IConnection> connection ) = 0;
			virtual void disconnect(void) = 0;
			virtual void send(Data * data, uint32_t length){};
			virtual void work(uint32_t n){};
			virtual bool hasFinished(void) = 0;
			virtual void close(void){};
			virtual void recv(std::string message){};
		};
	}
}

#endif // ITRANSPORT_HPP
