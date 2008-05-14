%module mod_sdlmouse

%{#include "love_sdlmouse.h"%}

namespace love_sdlmouse
{
	float getX();
	float getY();
	void setPosition(float x, float y);
	bool isDown(int button);
	void setVisible(bool visible);
	bool isVisible();
}

%luacode {
love.mouse = mod_sdlmouse
}