
#ifndef LOVE_LOAD_GAME_H
#define LOVE_LOAD_GAME_H

#include "LoadTest.h"
#include "Loader.h"
#include "LoadListener.h"
#include "Game.h"
#include "Font.h"

using namespace love;


/**
* @brief LoadGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-09-09
* @brief 
**/
class LoadGame : public Game, public LoadListener
{
private:

	pLoader loader;
	Font * font;

public:



	LoadGame();
	~LoadGame();

	void init();
	void render();
	void update(float dt);
	void loadStateChanged();

};

#endif 
