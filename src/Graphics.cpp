#include "Graphics.h"
#include "Exception.h"

namespace love
{

	Graphics::Graphics()
		: print(0)
	{
	}

	bool Graphics::extra(const std::string & so)
	{
		try
		{
			clear = getf<fptr_void>(so, "clear");
			try_change = getf<fptr_try_change>(so, "try_change");
			present = getf<fptr_void>(so, "present");
			toggleFullscreen = getf<fptr_toggleFullscreen>(so, "toggleFullscreen");
			draw_console = getf<fptr_void>(so, "draw_console");
			print = getf<fptr_print>(so, "print");
		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return true;
	}
}
