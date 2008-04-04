#include "Game.h"

#include "Filesystem.h"
#include "Module.h"

namespace love
{

	Game::Game() : filesystem(0), consoleVisible(false)
	{
	}

	Game::~Game()
	{
	}

	bool Game::reload()
	{
		unload();
		return load();
	}

	void Game::setFilesystem(Filesystem * fs)
	{
		filesystem = fs;
	}

	bool Game::isConsoleVisible() const
	{
		return consoleVisible;
	}

	void Game::setConsoleVisible(bool visible)
	{
		this->consoleVisible = visible;
	}

} // love
