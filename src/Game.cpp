#include "Game.h"
#include "love.h"

namespace love
{

	Game::Game() : config(0)
	{
		setType(LOVE_TYPE_GAME);
		gui = 0;
	}

	Game::~Game()
	{
		if(config != 0) delete config;
		if(gui != 0) delete gui;
	}

	void Game::mousePressed(float x, float y, int state)
	{
	}

	void Game::mouseReleased(float x, float y, int state)
	{
	}

	void Game::mouseMoved(float x, float y)
	{
	}

	void Game::keyPressed(int key)
	{
	}

	void Game::keyReleased(int key)
	{
	}

	void Game::eventFired(pEvent e)
	{
	}

	void Game::suspend()
	{
	}

	void Game::resume()
	{	
		// Check if display mode has been changed
		if(getDisplayModeChangedNum() > 0)
		{
			// Okay, reload graphics then.
			reloadGraphics();
			resetDisplayModeListener();
		}
	}

	void Game::stop()
	{
		if(loaded)
			unload();
		loaded = false;
	}

	gcn::Container * Game::getGUI()
	{
		return gui;
	}

	const string & Game::getSource() const
	{
		return source;
	}

}//love