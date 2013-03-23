#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

#include "server.hpp"
#include "relay_client.hpp"
#include "bridge.hpp"

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 4)
    {
      std::cerr << "Usage: relay <local port> <remote host> <remote port>\n";
      return 1;
    }


	boost::shared_ptr<bridge> bridge( new bridge() );
	
	std::string local_port = argv[1];
	std::string remote_host = argv[2];
	std::string remote_port = argv[3];
	
    boost::asio::io_service io_service;

    boost::shared_ptr<server> s (
		new server(io_service
			, bridge
			, local_port
			, remote_host
			, remote_port
		)
	);
	bridge->set_server(s);

	boost::shared_ptr<relay_client> c (
		new relay_client(io_service
			,  bridge
			, remote_host
			, remote_port
		)
	);

	bridge->set_relay_client(c);
	boost::posix_time::ptime tick = boost::posix_time::microsec_clock::local_time();
	
	io_service.run();
	/* Use this instead of io_service.run()
	  if you wish to poll instead of letting the async ops take place in threads
	
	while (true){
		io_service.poll();
		
		boost::posix_time::ptime now  = boost::posix_time::microsec_clock::local_time();
		boost::posix_time::time_duration diff = tick - now;
		boost::this_thread::sleep( boost::posix_time::microseconds(100) );

		// The custom invocation hook adds the handlers to the priority queue
		// rather than executing them from within the poll_one() call.
		while (io_service.poll_one())
		  ;
		pri_queue->execute_all();
	}
	*/
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
