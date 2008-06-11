%module mod_system

%{#include "love_system.h"%}

namespace love_system
{
	const char * getVersion();
	const char * getCodename();
	const char * getPlatform();
	void error(const char * msg);
	void warning(const char * msg);
	void exit();
	void suspend();
	void resume();
	void restart();
	void grabInput(bool grab);
}

%native(include) int love_system::include(lua_State * L);

%luacode {
love.system = mod_system
}