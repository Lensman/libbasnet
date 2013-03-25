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
#include <boost/uuid/uuid_io.hpp>         

namespace aosnet{

	Protocol::Protocol( boost::uuids::uuid uuid, basnet::IListener * listener )
	{

		LOG(Log::logDEBUG4) << "NEW PROTOCOL STARTED:" << uuid;
		std::string tag = boost::uuids::to_string(uuid);
	
		connections[tag] = ( pConnection( (aosnet::IConnection*) new Connection(0, 32887, 4) ) );

		fPS onDisconnectCallback = boost::bind( &basnet::IListener::onDisconnect , listener, _1 );
		fPS onRecvCallback = boost::bind( &basnet::IListener::onRecv , listener, _1);

		transports[tag] = ( pTransport( 
					(aosnet::Transport::ITransport*)new aosnet::Transport::ENET::Transport(
					onDisconnectCallback
					, onRecvCallback
				)
			)
		);
		
		transports[tag]->connect(connections[tag] );
		
	}

	Protocol::~Protocol(){
		deleteAllTransports();
		LOG(Log::logDEBUG) << "Protocol REMOVED";
	}

	/* not impl yet */
    boost::shared_ptr<aosnet::IConnection> Protocol::getContext()
    {
        return nullptr;
    }

	uint32_t Protocol::getTransportCount()
	{
		return transports.size();
	}

	uint32_t Protocol::getFirstTransport()
	{
		return (uint32_t) &transports;
	}

	void Protocol::deleteAllTransports(void)
	{
		if ( transports.size() > 0) 
		for( std::map<std::string, pTransport>::iterator itr=transports.begin(); itr !=transports.end(); )
		{
			LOG(Log::logDEBUG)  << "Deleting transport " << itr->first; 
			itr->second->close();
			itr = transports.erase( itr );
		}
	}

	void Protocol::deleteTransport( char * tag )
	{
		if ( transports.size() > 0) 
		for( std::map<std::string, pTransport>::iterator itr=transports.begin(); itr !=transports.end(); )
		{
			if(itr->first == tag ){
				
				itr = transports.erase(itr);
				LOG(Log::logDEBUG)  << "closing " << tag 
					<< " from map now : " << transports.size();
			}
			else
			++itr;
		}
	}
}