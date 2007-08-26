/**
* @file LuaGameState.h
* @author Anders Ruud
* @date 2007-06-08
* @brief Contains definition for class LuaGameState.
**/

#ifndef LOVE_LUAGAMESTATE_H
#define LOVE_LUAGAMESTATE_H

// LOVE
#include "GameState.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

struct lua_State;

namespace love
{
	class Font;
	class Color;

	/**
	* @class LuaGameState
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-06-08
	* @brief 
	**/
	class LuaGameState : public GameState
	{
	private:

		lua_State * L;
		string script;

	public:

		/**
		* @brief Contructs an empty LuaGameState.
		**/
		LuaGameState();
		LuaGameState(GameObjectContainer * master, lua_State * L, const string & script);
		virtual ~LuaGameState();

		virtual void init();
		virtual void update(float dt);
		virtual void render();
		virtual void load();
		virtual void unload();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);

	};

	typedef boost::shared_ptr<LuaGameState> pLuaGameState;

} // love

#endif

