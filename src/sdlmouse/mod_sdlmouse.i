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

/**
* Mouse button constants.
**/
%constant const int left = 1;
%constant const int middle = 2;
%constant const int right = 3;
%constant const int wheelup = 4;
%constant const int wheeldown = 5;