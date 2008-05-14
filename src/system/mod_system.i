%module mod_system

%{#include "love_system.h"%}

namespace love_system
{
	const char * getVersion();
	const char * getCodename();
	const char * getPlatform();
	void exit();
}

%luacode {
love.system = mod_system
}