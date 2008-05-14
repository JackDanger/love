%module mod_sdlkeyboard

%{#include "love_sdlkeyboard.h"%}

namespace love_sdlkeyboard
{
	bool isDown(int key);	
}

%luacode {
love.keyboard = mod_sdlkeyboard
}