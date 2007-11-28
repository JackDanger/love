#include "NeoFontTexGame.h"

#include "love.h"
#include "Core.h"
#include "Mouse.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "GameConfiguration.h"
#include "love_keys.h"
#include <vector>
#include "Vector.h"

#include <cmath>

using love::Color;
using love::Vector;
using std::vector;

NeoFontTexGame::NeoFontTexGame()
{
}

NeoFontTexGame::~NeoFontTexGame()
{

}


int NeoFontTexGame::load()
{

	return love::LOVE_OK;
}

void NeoFontTexGame::unload()
{

	loaded = false;
}

void NeoFontTexGame::reloadGraphics()
{
}


int NeoFontTexGame::init()
{


	// Create game configuration
	config = new love::GameConfiguration();
	config->setTitle("Neo Font Tex Game");
	config->setAuthor("Grammaton Cleric Preston");





	inited = true;

	return love::LOVE_OK;
}

void NeoFontTexGame::render()
{

}

void NeoFontTexGame::update(float dt)
{

}

void NeoFontTexGame::keyPressed(int key)
{

}

void NeoFontTexGame::mousePressed(float x, float y, int button)
{

}
