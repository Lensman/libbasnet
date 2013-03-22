#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "ring_buffer_atomic.hpp"
//#include "message.hpp"

// Forward decl
class server;
class relay_client;
/* 

The bridge class allows a client and server to communicate, as messges are routed from the 
client to local server to remote server and vice versa on the return path.

player <-> local server port ???? <-> remote server port ????

Additionally, the atomic_ring_buffer class can be used as in intermediary store for messages
passing through this bridge. It is cheap to use and thread safe as long as there is only one
producer / consumer per bridge.

I've tried to keep this as low latency as possible, so it's best to avoid the intermediary store
unless it is really needed, such as when there is inequality between producer / consumer 
in either direction.

*/
class bridge : public boost::enable_shared_from_this<bridge>
{
public:
	bridge()
	{
	}
	void set_relay_client( boost::shared_ptr<relay_client> c ){
		c_ = c;
	}
	void set_server( boost::shared_ptr<server> s ){
		s_ = s;
	}
	/*
	void recv_from_client( message mess ){
		//outgoing_ring.push(mess);
	
	}
	void recv_from_server( message mess){
		//incoming_ring.push(mess);
	
	}
	bool get_relay_client_message(message& mess){
		
		return true;//incoming_ring.pop(mess) ;
	}
	bool get_server_message(message& mess){
		
		return true;//outgoing_ring.pop(mess) ;
	}
	*/
	boost::shared_ptr<relay_client> c_;
	boost::shared_ptr<server> s_;
private:
	//ring_buffer_atomic<message,512> incoming_ring;
	//ring_buffer_atomic<message,512> outgoing_ring;
};