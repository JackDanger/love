
#ifndef FONT_TEX_GAME_PONG_GAME_H
#define FONT_TEX_GAME_PONG_GAME_H


// LOVE
#include "Game.h"
#include "Font.h"
#include "Text.h"
#include "SmoothAnimatedColor.h"
#include "ImageFromFile.h"
#include "FrameAnimation.h"
#include "Loader.h"
#include "LoadListener.h"
#include "ConfigLoader.h"
#include "Actor.h"
#include "Particle.h"
#include "ParticleEmitter.h"

#include "Sound.h"
#include "Music.h"

#include "AnimatedColor.h"

#include "GUIText.h"
#include "Menu.h"

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

// STL
#include <string>
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

namespace love {

/**
* @brief FontTexGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-09-01
* @brief 
**/
class FontTexGame : public love::Game
{
private:

//sounds shit
public:


	/**
	* @brief Creates a new FontTexGame object.
	**/
	FontTexGame();

	~FontTexGame();

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

	/**
	* @brief Called when a key is pressed.
	* @param key The ASCII key code.
	**/
	void keyPressed(int key);

	void reloadGraphics();

};

} // love

#endif

