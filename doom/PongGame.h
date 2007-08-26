
#ifndef LOVE_PONG_GAME_H
#define LOVE_PONG_GAME_H

#include <string>
#include <map>

#include "Game.h"
#include "Keyboard.h"
#include "HierarchyGrid.h"

#include "Map.h"
#include "CollisionDetector.h"
#include "SimpleEntity.h"
#include "Container.h"
#include "SplashScreen.h"
#include "Font.h"


using namespace love;
using std::map;

/**
* @brief PongGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-08-26
* @brief 
**/
class PongGame : public Game
{
private:

	CollisionDetector coldet;

	Container<Body> bodies;

	int player1, player2, ball;

	int wall1, wall2;

	float bsx;
	float bsy;

	int balldirx;
	int balldiry;

	float mxl, myl, mx, my;

	Font * font;

public:


	/**
	* @brief Creates a new PongGame object.
	**/
	PongGame();

	~PongGame();

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
	void mousePressed(float x, float y, int state);

	/**
	* @brief Called when a mouse button is released.
	* @param x The x-coordinate of the event.
	* @param y The y-coordinate of the event.
	**/
	void mouseReleased(float x, float y, int state);

	void mouseMoved(float x, float y);

	void eventFired(Event e);
};

#endif 
