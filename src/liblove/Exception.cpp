#include <love/Exception.h>

namespace love
{
	Exception::Exception( std::string message ) : message(message) { }

	const std::string & Exception::msg() const throw()
	{
		return message;
	}

	const char * Exception::what() const throw()
	{
		return message.c_str();
	}
}
