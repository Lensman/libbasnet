#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>


class message
{
public:
  enum { header_length = 4 };
  enum { max_body_length = 2048 };
  message( )
    : body_length_(0)
  {
  }
  message( char* msg, size_t length )
    : body_length_(length)
  {
	  
	 std::strncpy( data_, msg, length );
	  //memset(data_,1,max_body_length);
  }
	void hexdump(void *ptr, int buflen)
	{
		unsigned char *buf = (unsigned char*)ptr;
		int i, j;
		for (i=0; i<buflen; i+=16)
		{
			printf("%06x: ", i);
			for (j=0; j<16; j++)
				if (i+j < buflen)
					printf("%02x ", buf[i+j]);
				else
					printf("   ");
			printf(" ");
			for (j=0; j<16; j++)
				if (i+j < buflen)
					printf("%c", isprint(buf[i+j]) ? buf[i+j] : '.');
			printf("\n");
		}
	}
  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  size_t length() const
  {
    return body_length_;
  }

  const char* body() const
  {
    return data_;
  }

  char* body()
  {
    return data_;
  }

  size_t body_length() const
  {
    return body_length_;
  }

  void body_length(size_t new_length)
  {
    body_length_ = new_length;
    if (body_length_ > max_body_length)
      body_length_ = max_body_length;
  }

private:
  char data_[max_body_length];
  size_t body_length_;
};

#endif // MESSAGE_HPP