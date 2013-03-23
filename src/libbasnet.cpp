#include "libbasnet/basnet.hpp"

namespace aosnet{
	namespace Factory{
		Protocol *p;

		extern void DLL_EXPORT startProtocol(char* tag){
			p = new Protocol(tag);
		}
		extern void DLL_EXPORT stopProtocol(char* tag){
			delete p;
		}
	}
}