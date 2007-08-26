/**
* @file GameState.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GameState.
**/

#ifndef LOVE_GAMESTATE_H
#define LOVE_GAMESTATE_H

// LOVE
#include "AbstractEntity.h"
#include "GameObjectContainer.h"
#include "Loadable.h"
#include "Resumable.h"
#include "KeyListener.h"
#include "MouseListener.h"


// STL

// Boost
#include <boost/shared_ptr.hpp>



namespace love
{

	/**
	* @class GameState
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GameState :	public AbstractEntity, public KeyListener, public MouseListener
	{
	public:

		virtual void init();
		virtual void update(float dt);
		virtual void render();

		virtual void keyPressed(int key);
		virtual void keyReleased(int key);
		virtual void mousePressed(float x, float y, int button);
		virtual void mouseReleased(float x, float y, int button);


		/**
		* @brief Contructs an empty GameState.
		**/
		GameState();
		virtual ~GameState();

	};

	typedef boost::shared_ptr<GameState> pGameState;

} // love

#endif

