%module mod_sdljoystick

%{#include "love_sdljoystick.h"%}

namespace love_sdljoystick
{
	int getNumJoysticks();
	const char * getName(int index);
	void open(int index);
	bool isOpen(int index);
	int getNumAxes(int index);
	int getNumBalls(int index);
	int getNumButtons(int index);
	int getNumHats(int index);
	float getAxis(int index, int axis);
	//native: getAxes
	//native: getBall
	bool isDown(int index, int button);
	int getHat(int index, int hat);
	void close(int index);
}

%native(getAxes) int love_sdljoystick::getAxes(lua_State * L);
%native(getBall) int love_sdljoystick::getBall(lua_State * L);

%luacode {
love.joystick = mod_sdljoystick
}