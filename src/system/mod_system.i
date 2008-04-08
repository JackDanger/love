%module mod_system

%{#include "love_system.h"%}

namespace love_system
{
	const char * getVersion();
	const char * getCodeName();
	const char * getPlatform();
	void exit();
	void restart();
	void suspend(); 
	void print(const char * msg);

}
