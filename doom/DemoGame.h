/**
* @file DemoGame.h
* @brief Contains definition of class DemoGame.
* @date 2006-03-12
* @author Anders Ruud
**/

#ifndef LOVE_DEMOGAME_H
#define LOVE_DEMOGAME_H

#include <string>
#include <map>

#include "Game.h"
#include "Keyboard.h"

#include "Color.h"
#include "Map.h"
#include "Font.h"
#include "ParticleEmitter.h"
#include "Attractor.h"
#include "Container.h"


using namespace love;
using std::map;

/**
* @class DemoGame
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-03-12
* @brief A demo of the LOVE engine so far.
*
* Later: An example of how to create a game in the engine.
**/
class DemoGame : public Game
{
private:

	Map * currentMap;

	//font testing
	Font *textman;

	ParticleEmitter * pam;

	vector<Attractor> attractors;

	float camera_x;
	float camera_y;


public:


	/**
	* @brief Creates a new DemoGame object.
	**/
	DemoGame();

	~DemoGame();

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

	/**
	* @brief Called when a key is pressed.
	* @param key The ASCII key code.
	**/
	void keyPressed(int key);

	/**
	* @brief Called when a key is released.
	* @param key The ASCII key code.
	**/
	void keyReleased(int key);

	/**
	* @brief Called when a mouse button is pressed.
	* @param x The x-coordinate of the event.
	* @param y The y-coordinate of the event.
	**/
	void mousePressed(float x, float y, int button);

	/**
	* @brief Called when a mouse button is released.
	* @param x The x-coordinate of the event.
	* @param y The y-coordinate of the event.
	**/
	void mouseReleased(float x, float y, int button);

	void mouseMoved(float x, float y);

};

#endif 
