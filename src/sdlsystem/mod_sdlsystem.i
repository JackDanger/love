%module mod_sdlsystem

%{#include "love_sdlsystem.h"%}

namespace mod_sdlsystem
{
	
}

%native(events) int love_sdlsystem::events(lua_State * L);

%luacode {
love.system = mod_sdlsystem
}