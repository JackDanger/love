#ifndef LOVE_EXCEPTION_H
#define LOVE_EXCEPTION_H

#include <exception>
#include <string>

namespace love
{
	class Exception : public std::exception
	{
	protected:
		std::string message;
	public:
		Exception( std::string message );
		~Exception() throw() {}
		const std::string & msg() const throw();
		virtual const char * what() const throw();
	};
}

#endif
