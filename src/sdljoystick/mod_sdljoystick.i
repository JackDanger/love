%module mod_sdljoystick

%{#include "love_sdljoystick.h"%}

namespace love_sdljoystick
{
	int getNumGamepads();
	const char * getName(int index);
	void open(int index);
	bool isOpen(int index);
	int getNumAxes(int index);
	int getNumBalls(int index);
	int getNumButtons(int index);
	int getNumHats(int index);
	int getAxis(int index, int axis);
	int getBallX(int index, int ball);
	int getBallY(int index, int ball);
	int getButton(int index, int button);
	int getHat(int index, int hat);
	void close(int index);
}

%luacode {
love.gamepad = mod_sdljoystick
}