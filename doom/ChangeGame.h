
#ifndef CHANGE_GAME_H
#define CHANGE_GAME_H


// LOVE
#include "Game.h"
#include "Font.h"
#include "ImageFromFile.h"
#include "FrameAnimation.h"
#include "Image.h"
#include "Actor.h"

using love::Font;



// STL
#include <string>
#include <map>

using std::map;

using love::pAbstractImage;
using love::ImageFromFile;
using love::pImage;
using love::Image;
using love::pFrameAnimation;
using love::pSprite;
using namespace love;

/**
* @brief ChangeGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-09-01
* @brief 
**/
class ChangeGame : public love::Game
{
private:

	pAbstractImage image;
	pImage oimg;

	pSprite sprite;
	pActor actor;

public:


	/**
	* @brief Creates a new ChangeGame object.
	**/
	ChangeGame();

	~ChangeGame();

	/**
	* @brief Initializes the game.
	**/
	void init();

	/**
	* @brief Renders the entire game once.
	**/
	void render();

	/**
	* @brief Updates the entire game.
	* @param dt The time since last frame (in seconds).
	**/
	void update(float dt);

	void load();

	void unload();
};

#endif 
