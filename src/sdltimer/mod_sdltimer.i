%module mod_sdltimer

%{#include "love_sdltimer.h"%}

namespace love_sdltimer
{
	float getDelta();
	float getFPS();	
	void sleep(int ms);
	float getTime();
}

%luacode {
love.timer = mod_sdltimer
}