#include "Game.h"

namespace love
{
	Game::~Game()
	{
	}

	bool Game::reload()
	{
		unload();
		return load();
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

	const std::string & Game::getSource() const
	{
		return source;
	}

}//love
