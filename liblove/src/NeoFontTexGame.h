
#ifndef LOVE_NEO_FONT_TEX_GAME_H
#define LOVE_NEO_FONT_TEX_GAME_H


// LOVE
#include "Game.h"
#include "ParticleSystem.h"
#include "SmoothAnimatedColor.h"
#include "AbstractImage.h"
#include "Font.h"


// STL
#include <string>
#include <map>
#include <vector>


/**
* @brief NeoFontTexGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2007-08-13
* @brief 
**/
class NeoFontTexGame : public love::Game
{

private:

	love::ParticleSystem * psys;
	love::AbstractImage * img;
	love::AnimatedColor * clr;
	love::Font * font;

	float r;


public:


	/**
	* @brief Creates a new NeoFontTexGame object.
	**/
	NeoFontTexGame();

	~NeoFontTexGame();

	/**
	* @brief Initializes the game.
	**/
	int init();

	/**
	* @brief Renders the entire game once.
	**/
	void render();

	/**
	* @brief Updates the entire game.
	* @param dt The time since last frame (in seconds).
	**/
	void update(float dt);

	int load();
	void unload();
	void reloadGraphics();

	/**
	* @brief Called when a key is pressed.
	* @param key The ASCII key code.
	**/
	void keyPressed(int key);

	void mousePressed(float x, float y, int button);


};

#endif
