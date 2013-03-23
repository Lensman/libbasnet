#pragma once
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "priority_queue.hpp"
#include "bridge.hpp"
#include "message.hpp"
/* 
only udp at the moment, but this will all be templated at some point in the future to
allow connecting sockets of any defined type.
*/
typedef boost::shared_ptr<boost::asio::ip::udp::socket> socket_type;
typedef boost::asio::ip::udp::endpoint endpoint_type;
typedef boost::asio::ip::udp::resolver::iterator iterator_type;

class server : public boost::enable_shared_from_this<server>
{
public:
	server( boost::asio::io_service&
		, boost::shared_ptr<bridge>
		, std::string
		, std::string, std::string );
	void start_receive();
	void handle_receive_from(const boost::system::error_code&, size_t);
	void send_handler(const boost::system::error_code&, size_t );
	void send();
	void send(boost::shared_ptr<std::string>);
private:
	iterator_type iterator;
	boost::asio::io_service& io_service_;

	enum { max_length = 2048 };
	socket_type socket_;
	endpoint_type sender_endpoint_;
	char data_[max_length];

	boost::shared_ptr<bridge> bridge_;

};
typedef boost::shared_ptr<server> server_ptr;