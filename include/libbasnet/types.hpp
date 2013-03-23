#pragma once
#include <boost/function.hpp>

namespace aosnet{

	typedef  char * Data;
	typedef enum Types{ ENET, DUMMY };
	typedef boost::function<void(void)> fP;
	typedef boost::function<void(std::string)> fPS;

}