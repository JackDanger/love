/**
* @file LuaScriptableEntity.h
* @author Anders Ruud
* @date 2007-06-01
* @brief Contains definition for class LuaScriptableEntity.
**/

#ifndef LOVE_LUASCRIPTABLE_H
#define LOVE_LUASCRIPTABLE_H

// LOVE
#include "Entity.h"
#include "Scriptable.h"

// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

using std::vector;
using std::string;

struct lua_State;

namespace love
{


	/**
	* @class LuaScriptableEntity
	* @version 1.0
	* @since 1.0
	* @author 
	* @date 2007-06-01
	* @brief 
	**/
	class LuaScriptableEntity : public Entity
	{
	private:

		lua_State * L;

	public:

		/**
		* @brief Constructor.
		**/
		LuaScriptableEntity();
		virtual ~LuaScriptableEntity();

		/**
		* @brief Sets the pointer to the Lua state.
		* @param L The Lua state.
		**/
		void setLuaState(lua_State * L);

		/**
		* @brief Loads the LuaScriptableEntity.
		* 
		* Checks which methods are available.
		**/
		virtual void load();

		/**
		* @brief Updates the LuaScriptableEntity.
		* @param dt The time since last update.
		*
		* Checks if scripted update exists. If it does, it calls that. Otherwise
		* it calls baseUpdate().
		**/
		virtual void update(float dt);

		/**
		* @brief The update method that is called if no scripted update is present.
		* @param dt The time since last update.
		**/
		virtual void baseUpdate(float dt);

		/**
		* @brief Renders the LuaScriptableEntity.
		*
		* Checks if scripted render exists. If it does, it calls that. Otherwise
		* it calls baseRender().
		**/
		virtual void render();


		/**
		* @brief The render that will be called if no scriptable render is present.
		**/
		virtual void baseRender();


	};

	typedef boost::shared_ptr<LuaScriptableEntity> pLuaScriptableEntity;

} // love

#endif

