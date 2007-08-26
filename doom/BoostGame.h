
#ifndef LOVE_BOOST_GAME_H
#define LOVE_BOOST_GAME_H

// LOVE
#include "Game.h"
#include "Point.h"
#include "Container.h"


using love::Game;
using love::Point;
using love::Container;

namespace love
{
	class Entity;
}

// boost
#include <boost/shared_ptr.hpp>

/**
* @brief BoostGame 
* @version 1.0
* @since 1.0
* @author Anders Ruud
* @date 2006-09-09
* @brief 
**/
class BoostGame : public Game
{
private:


public:

	boost::shared_ptr<love::Entity> s1;
	Container<love::Point> cp;

	BoostGame();
	~BoostGame();

	void init();
	void render();
	void update(float dt);

};

#endif 
