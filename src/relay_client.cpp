#include "relay_client.hpp"
#include "server.hpp"
#include "bridge.hpp"

#include <boost/bind.hpp>
#include <iostream>


	relay_client::relay_client( boost::asio::io_service& io_service
	  , boost::shared_ptr<bridge> bridge
	  , std::string remote_host
	  , std::string remote_port )
    : io_service_(io_service)
	{
		bridge_ = bridge;

		boost::asio::ip::udp::resolver resolver(io_service_);
		boost::asio::ip::udp::resolver::query query2(boost::asio::ip::udp::v4(), remote_host, remote_port);
		remote_endpoint_ = *resolver.resolve(query2);
		remote_socket_ = boost::shared_ptr<boost::asio::ip::udp::socket>(new boost::asio::ip::udp::socket(io_service_));
		remote_socket_->open( boost::asio::ip::udp::v4());
		remote_socket_->async_connect(remote_endpoint_, 
			boost::bind(&relay_client::connect_handler, this,
			  boost::asio::placeholders::error));
	}

	void relay_client::start_receive(){
		remote_socket_->async_receive(
          boost::asio::buffer(remote_data_, max_length),
          boost::bind(&relay_client::recv_handler, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
	}
	void relay_client::connect_handler(const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Client connected: " << remote_endpoint_.address() << " remote port: " << remote_endpoint_.port() << std::endl;
			//boost::function<void()> f = boost::bind( &relay_client::check, this );
			//io_service_.post(queue_->wrap(123, f));
			start_receive();
		}
	}

	void relay_client::send(boost::shared_ptr<std::string> in_message)
	{
		remote_socket_->async_send_to(
			  boost::asio::buffer(in_message->data(), in_message->length() )
			, remote_endpoint_
			, boost::bind(
				  &relay_client::send_handler
				, this
				, boost::asio::placeholders::error
				, boost::asio::placeholders::bytes_transferred
			)
		);
	}
	void relay_client::send()
	{
		/*
		message in_message;
		int cnt=0;
		while (bridge_->get_relay_client_message(in_message)){
			std::cout << "client send cnt:" << cnt << std::endl;
			cnt++;
		remote_socket_->async_send(boost::asio::buffer(in_message.data(), in_message.body_length() ),
		boost::bind(&relay_client::send_handler, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
		}
		*/
	}

	void relay_client::send_handler( const boost::system::error_code& error,
		size_t bytes_recvd
		)
	{
		if (error)
		{
			std::cout << "******Client send  err:" << error << std::endl;
		}
	}
	void relay_client::recv_handler(const boost::system::error_code& error,
		size_t bytes_recvd
		)
	{
		if (!error)
		{

		boost::shared_ptr<std::string> p( new std::string( remote_data_, bytes_recvd ) );
		bridge_->s_->send(p);

		start_receive();

		}else{
			std::cout << "**********Client err:" << error << std::endl;
		}
	}
