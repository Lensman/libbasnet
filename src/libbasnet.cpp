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
#include "libbasnet/IListener.hpp"

#include <boost/uuid/uuid.hpp>            
#include <boost/uuid/uuid_generators.hpp> 
#include <boost/uuid/uuid_io.hpp>    
#pragma warning(disable:4996)

namespace aosnet{
	namespace Factory{
		Protocol *p;

		extern void DLL_EXPORT startProtocol( basnet::IListener* interestedParty )
		{
			if ( p == nullptr )
				p = new Protocol(boost::uuids::random_generator()(), interestedParty);	
		}

		extern void DLL_EXPORT startVanillaProtocol( basnet::IListener* interestedParty )
		{
			if ( p == nullptr )
				p = new Protocol(boost::uuids::random_generator()(), interestedParty);	
		}

		extern void DLL_EXPORT stopProtocol()
		{
			if ( p != nullptr )
				delete p;
		}

		extern void DLL_EXPORT registerListener( basnet::IListener* interestedParty )
		{
			 interestedParty->onRecv( std::string( "you want?" ) );
		}
	}
}