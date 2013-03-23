#ifndef RELAY_CLIENT_HPP
#define RELAY_CLIENT_HPP
#pragma once
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "bridge.hpp"


typedef boost::shared_ptr<boost::asio::ip::udp::socket> socket_type;
typedef boost::asio::ip::udp::endpoint endpoint_type;

class relay_client : public boost::enable_shared_from_this<relay_client>
{
public:
	relay_client( boost::asio::io_service& io_service
	  , boost::shared_ptr<bridge> bridge
	  , std::string remote_host
	  , std::string remote_port );
	void start_receive();
	void connect_handler(const boost::system::error_code&);
	void send(boost::shared_ptr<std::string>);
	void send();
	void send_handler( const boost::system::error_code&, size_t );
	void recv_handler(const boost::system::error_code&,size_t );

private:
	boost::asio::io_service& io_service_;

	enum { max_length = 2048 };
	socket_type remote_socket_;
	endpoint_type remote_endpoint_;
	
	char remote_data_[max_length];
	boost::shared_ptr<bridge> bridge_;
};
typedef boost::shared_ptr<void> relay_client_ptr;
#endif // RELAY_CLIENT_HPP