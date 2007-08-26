#include "GameState.h"

namespace love
{

	GameState::GameState() : master(0)
	{
		setType(LOVE_TYPE_GAME_STATE);
	}

	GameState::GameState(GameObjectContainer * master) : master(master)
	{
		setType(LOVE_TYPE_GAME_STATE);
	}

	void GameState::usingSprite(const char * key)
	{
		// @todo
		//obj.sprites[key] = master->sprites[key];
	}

	void GameState::usingLoadable(const char * key)
	{
		// @todo
		//obj.loadables[key] = master->loadables[key];
	}

	void GameState::usingImage(const char * key)
	{
		// Check for existence
		if(!master->abstractImages.contains(key)) return;

		// Okay, add to containers
		obj.abstractImages[key] = master->abstractImages[key];
		usingSprite(key);
		usingLoadable(key);
	}

	void GameState::usingFrameAnimation(const char * key)
	{
		// Check for existence
		if(!master->frameAnimations.contains(key)) return;

		// Okay, add to containers
		obj.frameAnimations[key] = master->frameAnimations[key];
		usingSprite(key);
		usingLoadable(key);
	}

	void GameState::usingFonts(const char * key)
	{
		// Check for existence
		if(!master->fonts.contains(key)) return;

		// Okay, add to containers
		obj.fonts[key] = master->fonts[key];
		usingLoadable(key);
	}

	void GameState::usingColor(const char * key)
	{
		// Check for existence
		if(!master->colors.contains(key)) return;

		// Okay, add to containers
		obj.colors[key] = master->colors[key];
		usingLoadable(key);
	}

	void GameState::usingActor(const char * key)
	{
		// Check for existence
		if(!master->actors.contains(key)) return;

		// Okay, add to containers
		obj.actors[key] = master->actors[key];
		usingLoadable(key);
	}


	void GameState::init()
	{
	}

	void GameState::update(float dt)
	{
	}

	void GameState::render()
	{
	}

	void GameState::load()
	{
	}

	void GameState::unload()
	{
	}

	void GameState::resume()
	{
		glClearColor((float)backgroundColor->getRed()/255.0f, (float)backgroundColor->getGreen()/255.0f, (float)backgroundColor->getBlue()/255.0f, 1.0f);
	}

	void GameState::reloadGraphics()
	{

		for(obj.abstractImages.begin(); !obj.abstractImages.end(); obj.abstractImages.next())
			obj.abstractImages.value()->load();

		for(obj.fonts.begin(); !obj.fonts.end(); obj.fonts.next())
			obj.fonts.value()->load();
	}


	void GameState::setFont(const char * key)
	{
		currentFont = obj.fonts[key].get();
	}

	void GameState::setFont(Font * font)
	{
		currentFont = font;
	}


	void GameState::setColor(Color * color)
	{
		this->currentColor = color;
	}

	void GameState::setColor(const char * key)
	{
		this->currentColor = obj.colors[key].get();
	}

	void GameState::setBackground(Color * color)
	{
		backgroundColor = color;
	}

	void GameState::setBackground(const char * key)
	{
		backgroundColor = obj.colors[key].get();
	}


	GameState::~GameState()
	{
	}


}// love
