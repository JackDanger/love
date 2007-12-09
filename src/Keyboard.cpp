#include "Keyboard.h"
#include "Core.h"
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
			core->printf("Keyboard: Key code '%d' is out of bounds.", key);

		keys[key] = true;
	}

	void Keyboard::keyReleased(int key)
	{
		if(key > NUM_KEYS)
			core->printf("Keyboard: Key code '%d' is out of bounds.", key);

		keys[key] = false;
	}

	bool Keyboard::isDown(int key)
	{
		if(key > NUM_KEYS)
			core->printf("Keyboard: Key code '%d' is out of bounds.", key);

		return keys[key] == true;
	}



}//love
