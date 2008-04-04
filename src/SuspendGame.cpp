#include "SuspendGame.h"
#include "constants.h"
#include "love.h"
#include "Timer.h"



namespace love
{

	extern Timer timer;

	SuspendGame::SuspendGame()
	{
	}

	SuspendGame::~SuspendGame()
	{
	}

	bool SuspendGame::load()
	{
		return true;
	}

	bool SuspendGame::unload()
	{
		return true;
	}


	bool SuspendGame::isConsoleVisible() const
	{
		// Console should always be visible when running this game.
		return true;
	}

	bool SuspendGame::require(Module & m)
	{
		// Not that kind of game.
		return true;
	}

	void SuspendGame::update(float dt)
	{
		// Save CPU in suspended mode.
		timer.sleep(100);
	}

	void SuspendGame::draw()
	{
	}

	void SuspendGame::keyPressed(int key)
	{
		if(key == KEY_r)
		{
			print("Restarting.");
			pop();
			restart();
		}
		else if(key == KEY_c)
		{
			print("Continuing.");
			pop();
		}
	}

	void SuspendGame::keyReleased(int key)
	{
	}

	void SuspendGame::mousePressed(int x, int y, int button)
	{
	}

	void SuspendGame::mouseReleased(int x, int y, int button)
	{
	}

	void SuspendGame::mouseMoved(int xrel, int yrel)
	{
	}

} // love
