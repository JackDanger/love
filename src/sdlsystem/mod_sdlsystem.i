%module mod_sdlsystem

%{#include "love_sdlsystem.h"%}

namespace mod_sdlsystem
{
	const char * getVersion();
	const char * getCodename();
	const char * getPlatform();
	
	void exit();
	void restart();
	
	void grabInput(bool grab);
}

%native(events) int love_sdlsystem::events(lua_State * L);

%luacode {
love.system = mod_sdlsystem
}