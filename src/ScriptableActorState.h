#ifndef LOVE_SCRIPTABLE_ACTOR_STATE_H
#define LOVE_SCRIPTABLE_ACTOR_STATE_H

#include "ActorState.h"

struct lua_State;

namespace love
{
	/**
	* @class ScriptableActorState
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-04-06
	* @brief A scriptable state for use with the Actor class.
	**/
	class ScriptableActorState : public ActorState
	{
	private:
		lua_State * L;

	public:
		/**
		 * @param parent The parent Actor.
		 * @param state The current Lua state.
		 * @param scriptname The name of the script that this state will utilize.
	 	 * @brief Contructs an empty ScriptableActorState and sets the parent actor, the lua state and the "chunk" name.
	 	 **/
		ScriptableActorState(Actor * parent, lua_State * state, const char * scriptname);

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		~ScriptableActorState();

		/**
		 * @brief Searches the lua script for the "chunk" associated with this state.
		 **/
		void init();

		/**
		 * @brief If the "chunk" associated with this state has a render function then it calls that; else it calls the default.
		 **/
		void render();

		/**
		 * @param dt The elapsed time in milliseconds.
		 * @brief If the "chunk" associated with this state has an update function then it calls that; else it calls the default.
		 **/
		void update(float dt);

		/**
		 * @brief Does nothing.
		 **/
		int load();

		/**
		 * @brief Does nothing.
		 **/
		void unload();
	};
}

#endif
