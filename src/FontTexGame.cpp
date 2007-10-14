#include "FontTexGame.h"
#include "Core.h"
#include "love.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "DisplayMode.h"
#include "GameConfiguration.h"

using love::GameConfiguration;

namespace love {
FontTexGame::FontTexGame()
{
}

FontTexGame::~FontTexGame()
{

}


int FontTexGame::load()
{
	loaded = true;

	return LOVE_OK;
}

void FontTexGame::unload()
{
	//THIS COULD BE IMPORTANT LOL
	//Mix_CloseAudio();
}


int FontTexGame::init()
{
	
	config = new love::GameConfiguration();
	config->setTitle("FontTexGame");
	config->setAuthor("Grammaton Cleric Preston");
	config->setDisplayMode(DisplayMode(1024, 768));
	config->load();

	inited = true;
	return LOVE_OK;
}

void FontTexGame::render()
{
}

void FontTexGame::update(float dt)
{
	//gui->logic();
	//shiny->update(dt);
	//alsoshiny->update(dt);
}

void FontTexGame::keyPressed(int key)
{
	printf("Key: %d\n", key);
}

void FontTexGame::reloadGraphics()
{
	inited = inited;
}

} // love
