#ifndef BASNET_HPP
#define BASNET_HPP
#include "types.hpp"


#if ( defined _WIN32 || defined __CYGWIN__ ) & defined BUILD_DLL
  #define DLL_IMPORT __declspec(dllimport)
  #define DLL_EXPORT __declspec(dllexport)
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_IMPORT __attribute__ ((visibility ("default")))
    #define DLL_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_IMPORT
    #define DLL_EXPORT
    #define DLL_LOCAL
  #endif
#endif


#ifndef LOG_HPP
#include "log.hpp"
#endif
#include "Protocol.hpp"
#include "Connection.hpp"
#include "Transport.hpp"
#endif
