#include "server.hpp"
#include "relay_client.hpp"
#include "message.hpp"

typedef boost::asio::ip::udp::resolver resolver_type;

server::server(boost::asio::io_service& io_service
	, boost::shared_ptr<bridge> bridge
	, std::string local_port
	, std::string remote_host
	, std::string remote_port)
    : io_service_(io_service)
{
	bridge_ = bridge;

	resolver_type resolver(io_service_);
	resolver_type::query query(
		boost::asio::ip::udp::v4()
		, "localhost"
		, local_port
	);

	sender_endpoint_ = *resolver.resolve(query);

	socket_ = boost::shared_ptr<boost::asio::ip::udp::socket>(
		new boost::asio::ip::udp::socket(
			io_service_
			, sender_endpoint_
		)
	);
	
	std::cout 
	<< "server started on address: " <<  sender_endpoint_.address()
	<< " capacity: " << sender_endpoint_.capacity() 
	<< " port: " << sender_endpoint_.port()
	<< " size: " << sender_endpoint_.size()
	<< std::endl;

	start_receive();
}

void server::start_receive(){
	socket_->async_receive_from( boost::asio::buffer(data_, max_length)
		, sender_endpoint_
		, boost::bind( &server::handle_receive_from
			, this
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred
		)
	);
}

void server::handle_receive_from(const boost::system::error_code& error,
size_t bytes_recvd)
{
	if (!error && bytes_recvd > 0)
	{
		boost::shared_ptr<std::string> p(new std::string(data_, bytes_recvd));
		bridge_->c_->send( p );
		start_receive();
	}else{
		std::cout << "*********error" << error << std::endl;
	}
}

void server::send_handler( const boost::system::error_code& error, size_t bytes_recvd )
{
	// Do nothing function is the end of send chain 
	if (error)
	{
		std::cout << "*********server err : " << bytes_recvd << "err: " << error << std::endl;
	}
}

void server::send(boost::shared_ptr<std::string> in_message)
{
	socket_->async_send_to( boost::asio::buffer(in_message->data(), in_message->length() )
		, sender_endpoint_
		, boost::bind( &server::send_handler
			, this
			, boost::asio::placeholders::error
			, boost::asio::placeholders::bytes_transferred
		)
	);
}

void server::send()
{
	/*
	message in_message;

	while (bridge_->get_server_message(in_message))
	{
		socket_->async_send_to(boost::asio::buffer(in_message.body(), in_message.body_length() )
			, sender_endpoint_
			, boost::bind(&server::send_handler
				, this
				, boost::asio::placeholders::error
				, boost::asio::placeholders::bytes_transferred
			)
		);
	}
	*/
}