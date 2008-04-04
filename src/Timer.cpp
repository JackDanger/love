#include "Timer.h"
#include "Exception.h"

namespace love
{
	bool Timer::extra(const std::string & so)
	{
		try
		{
			step = getf<fptr_void>(so, "step");
			getDelta = getf<fptr_getDelta>(so, "getDelta");
			sleep = getf<fptr_sleep>(so, "sleep");
		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return true;		
	}

} // love
