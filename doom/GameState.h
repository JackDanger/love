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
	class GameState :	public AbstractEntity, public Loadable, public Resumable,
						public KeyListener, public MouseListener
	{
	protected:

		// All the objects this gamestate uses
		GameObjectContainer obj;

		// The master GameObjectContainer
		GameObjectContainer * master;

		// The current font. 
		Font * currentFont;

		// Text and primitives will be rendered with this color.
		Color * currentColor;
		Color * backgroundColor;

		// Internal using
		void usingSprite(const char * key);
		void usingLoadable(const char * key);

		virtual void init();
		virtual void update(float dt);
		virtual void render();
		virtual void load();
		virtual void unload();



	public:

		/**
		* @brief Contructs an empty GameState.
		**/
		GameState();
		
		GameState(GameObjectContainer * master);

		// 
		void usingImage(const char * key);
		void usingFrameAnimation(const char * key);
		void usingFonts(const char * key);
		void usingColor(const char * key);
		void usingActor(const char * key);

		void setFont(const char * key);
		void setFont(Font * font);

		void setColor(Color * color);
		void setColor(const char * key);
		void setBackground(Color * color);
		void setBackground(const char * key);

		virtual void reloadGraphics();
		virtual void resume();

		virtual ~GameState();

	};

	typedef boost::shared_ptr<GameState> pGameState;

} // love

#endif

