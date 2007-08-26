#include "GameControlEvent.h"

namespace love
{

	GameControlEvent::GameControlEvent(int mode, const string & game) : mode(mode), game(game)
	{
		setType(LOVE_TYPE_GAME_CONTROL_EVENT);
	}

	GameControlEvent::~GameControlEvent()
	{
	}

	int GameControlEvent::getMode() const
	{
		return mode;
	}

	void GameControlEvent::setMode(int mode)
	{
		this->mode = mode;
	}

	const string & GameControlEvent::getGame() const
	{
		return game;
	}

	void GameControlEvent::setGame(string game)
	{
		this->game = game;
	}


}// love
