%module mod_sdljoystick

%{#include "love_sdljoystick.h"%}

namespace love_sdljoystick
{
	int test();
}

%luacode {
love.gamepad = mod_sdljoystick
}