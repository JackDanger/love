%{
#include "using_game.h"
#include "LuaGame.h"
#include "Filesystem.h"
#include "love_file.h"
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
	void include(const char * file, int src = love::LOVE_GAMEDIR)
	{
		love::LuaGame * luagame = dynamic_cast<love::LuaGame *>(love::game);
		
		if(luagame != 0)
			luagame->include(std::string(file), src);
	}
	

	void open(const love::pFile * file)
	{
		(*file)->open();
	}
	
	void close(const love::pFile * file)
	{
		(*file)->close();
	}
	
	void write(const love::pFile * file, const char * data)
	{
		(*file)->write(std::string(data));
	}
	
	const char * read(const love::pFile * file)
	{
		return (*file)->read();
	}
}