
#include "libbasnet/basnet.hpp"



namespace aosnet{

	Protocol::Protocol( char* tag )
	{
		LOG(Log::logDEBUG4) << "NEW PROTOCOL STARTED" << tag;

		connections[tag] = ( pConnection( (aosnet::IConnection*) new Connection() ) );

		fPS onDisconnectCallback = boost::bind( &IConnection::onDisconnect , connections[tag], _1 );
		fPS onRecvCallback = boost::bind( &IConnection::onRecv , connections[tag], _1);

		transports[tag] = ( pTransport( 
					(aosnet::Transport::ITransport*)new aosnet::Transport::Dummy::Transport(
					onDisconnectCallback
					, onRecvCallback
				)
			)
		);
		transports[tag]->connect(connections[tag]);
		
	}

	Protocol::~Protocol(){
		deleteAllTransports();
		LOG(Log::logDEBUG) << "Protocol REMOVED";
	}

    boost::shared_ptr<aosnet::IConnection> Protocol::getContext()
    {
		LOG(Log::logDEBUG) << "NEW CONTEXT ADDED";
		boost::shared_ptr<aosnet::IConnection> p( (aosnet::IConnection*)new Connection() );
		
        return p;
    }

	uint32_t Protocol::getTransportCount(){
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
	
			itr = transports.erase(itr);
			//++itr;
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