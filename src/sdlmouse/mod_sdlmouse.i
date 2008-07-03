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

%native(getPosition) int love_sdlmouse::getPosition(lua_State * L);

%luacode {
love.mouse = mod_sdlmouse
}