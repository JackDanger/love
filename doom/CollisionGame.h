/**
* @file DemoGame.h
* @brief Contains definition of class DemoGame.
* @date 2006-03-12
* @author Anders Ruud
**/

#ifndef LOVE_COLLISION_GAME_H
#define LOVE_COLLISION_GAME_H

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


using namespace love;
using std::map;

/**
* @class CollisionGame
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-08-21
* @brief 
**/
class CollisionGame : public Game
{
private:

	Container<Body *> bodies;

	Map * currentMap;

	SplashScreen * ss;

	CollisionDetector coldet;

	HierarchyGrid * hgrid;

	Body * player;

	bool forces;

	bool useSpatialPartitioning;


public:

	static int playerId;

	Body * createBody3p(Vextor position, Vextor p1, Vextor p2, Vextor p3, float mass = 0.7f);
	Body * createBody4p(Vextor position, Vextor p1, Vextor p2, Vextor p3, Vextor p4, float mass = 0.7f);

	/**
	* @brief Creates a new DemoGame object.
	**/
	CollisionGame();

	~CollisionGame();

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
	void mousePressed(float x, float y);

	/**
	* @brief Called when a mouse button is released.
	* @param x The x-coordinate of the event.
	* @param y The y-coordinate of the event.
	**/
	void mouseReleased(float x, float y);

	void eventFired(Event e);
};

#endif 
