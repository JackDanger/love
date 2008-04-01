#include "Keyboard.h"
#include "Exception.h"

namespace love
{
	bool Keyboard::extra(const std::string & so)
	{
		try
		{
			isDown = getf<fptr_isDown>(so, "isDown");
		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return true;
	}

} // love
