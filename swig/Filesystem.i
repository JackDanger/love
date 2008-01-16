%{
#include "using_game.h"
#include "LuaGame.h"
#include "Filesystem.h"
%}

namespace love
{
	class Filesystem : public Device
	{
	public:	
	};
}

// Extensions
%extend love::Filesystem 
{
	void include(const char * file)
	{
		love::LuaGame * luagame = dynamic_cast<love::LuaGame *>(love::game);
		
		if(luagame != 0)
			luagame->include(std::string(file));
	}
}