#ifndef LOG_HPP
#define LOG_HPP

#include <sstream>
#include <iostream> 

#include "libbasnet/basnet.hpp"

class Log
{
public:
   enum TLogLevel {logERROR, logWARNING, logINFO, logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4};
   Log(){};
   static  TLogLevel& ReportingLevel();

	std::ostringstream& Get(TLogLevel level = logINFO)
	{
	   os << " " << level << ": ";
	   os << std::string(level > logDEBUG ? 0 : level - logDEBUG, '\t');
	   messageLevel = level;
	   return os;
	}
	virtual ~Log()
	{
		os << std::endl;
		std::string const& str = os.str();
		char const* outstring = str.c_str();

		fprintf(stderr, "%s", outstring );
		fflush(stderr);
	}
protected:
	std::ostringstream os;
private:
   
   Log(const Log&);
   Log& operator =(const Log&);
private:
   TLogLevel messageLevel;
};


#define LOG(level) \
if (level > Log::logDEBUG4) ; \
else Log().Get(level)

#endif