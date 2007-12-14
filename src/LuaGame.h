/**
* @file LuaGame.h
* @author Anders Ruud
* @date 2006-11-06
* @brief Contains definition for class LuaGame.
**/

#ifndef LOVE_LUAGAME_H
#define LOVE_LUAGAME_H


// LOVE
#include "Game.h"
#include "AbstractGraphics.h"
//#include "AbstractGUI.h"
#include "GUIContainer.h"

// STL
#include <set>

// Lua
extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

namespace love
{

	/**
	* @class LuaGame
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-06
	* @brief 
	**/
	class LuaGame : public Game
	{
	private:

		// Our Lua VM state.
		lua_State * L;

		// A list of all included files.
		std::set<std::string> included;

		// The graphics contexct.
		AbstractGraphics * gfx;

	public:

		/**
		* @brief Contructs an empty LuaGame.
		* @param source The source for the game. Can be directory or archive file. (.love only)
		**/
		LuaGame(const std::string & source);

		/**
		* @brief Destructor.
		**/
		virtual ~LuaGame();

		/**
		* @brief Initializes the game.
		**/
		int init();

		/**
		* @brief Loads the game.
		* @return LOVE_OK if no errors, false otherwise.
		**/
		int load();

		/**
		* @brief Unloads the game. 
		**/
		void unload();

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
		* @brief Called when the game is suspended. (Not stopped). 
		* @note By default, games will not be suspended. (Only stopped).
		**/
		void suspend();

		/**
		* @brief Called when a game is resumed from suspension.
		**/
		void resume();

		/**
		* @brief Called when the graphics needs to be reloaded.
		**/
		void reloadGraphics();

		/**
		* @brief Called when a key is pressed.
		* @param key The key that is pressed.
		**/
		void keyPressed(int key);

		/**
		* @brief Called when a key is released.
		* @param key The key that was released.
		**/
		void keyReleased(int key);

		/**
		* @brief Called when a mouse button is pressed.
		* @param x The x-coordinate of the mouse position.
		* @param y The y-coordinate of the mouse position.
		* @param button The button that was pressed.
		**/
		void mousePressed(float x, float y, int button);

		/**
		* @brief Called when a mouse button is released.
		* @param x The x-coordinate of the mouse position.
		* @param y The y-coordinate of the mouse position.
		* @param button The button that was released.
		**/
		void mouseReleased(float x, float y, int button);

		/**
		* @brief Called when some event is fired.
		* @param e The event that was fired.
		**/
		void eventFired(pEvent e);
		
		/**
		* @brief Reads and parses a Lua-file.
		* This method checks if the file already is included, and
		* does not include if it is.
		* 
		* @param filename The filname and path to the file.
		**/
		void include(const char * filename);

	};

} // love

#endif
