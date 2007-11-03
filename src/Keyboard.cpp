#include "Keyboard.h"
#include "love.h"

namespace love
{


	Keyboard::Keyboard()
	{
		setType(LOVE_TYPE_KEYBOARD);
	}

	Keyboard::~Keyboard()
	{
	}

	int Keyboard::init()
	{
		return LOVE_OK;
	}

	void Keyboard::keyPressed(int key)
	{

		if(key > NUM_KEYS)
			printf("Warning: Out of bounds @ Keyboard");

		keys[key] = true;
	}

	void Keyboard::keyReleased(int key)
	{
		if(key > NUM_KEYS)
			printf("Warning: Out of bounds @ Keyboard");

		keys[key] = false;
	}

	bool Keyboard::isDown(int key)
	{
		if(key > NUM_KEYS)
			printf("Warning: Out of bounds @ Keyboard");

		return keys[key] == true;
	}



}//love
