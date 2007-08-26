#ifndef LOVE_ACTOR_H
#define LOVE_ACTOR_H

#include "AbstractEntity.h"
#include "ScriptableActorState.h"
#include "Container.h"
#include "Loadable.h"
#include "Sprite.h"
#include <boost/shared_ptr.hpp>

struct lua_State;

namespace love
{
	/**
	* @class Actor
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-04-06
	* @brief An actor within the game; a scriptable entity.
	**/
	class Actor : public AbstractEntity, public Loadable
	{
	private:
		
		Container<Sprite> * sprites;
		ActorState * currentState;
		lua_State * L;
		Container<ActorState> states;

	public:

		/**
	 	 * @brief Contructs an empty actor with one ActorState (default).
	 	 **/
		Actor();

		/**
		 * @param L Pointer to the current Lua state.
		 * @param sprites Pointer to a container of Sprite objects.
		 * @brief Contructs an empty actor with one ActorState (default) and allows for scripting and retrieving sprites by key.
		 **/
		//Actor(lua_State * L, Container<Sprite> * sprites);

		/**
		 * @param L Pointer to the current Lua state.
		 * @param sprites Pointer to a container of Sprite objects.
		 * @param scriptname The name of the script that will be used by the ScriptableActorState.
		 * @brief Contructs an empty actor with one ScriptableActorState (default) with the appropriate script and allows for scripting and retrieving sprites by key.
		 **/
		Actor(lua_State * L, Container<Sprite> * sprites, const char * scriptname = "");

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		~Actor();

		/**
		 * @param name The name of the state.
		 * @return Pointer the new ActorState.
		 * @brief Creates an empty ActorState and adds it to the Container with the name parameter as key.
		 **/
		ActorState* addState(const char * name);

		/**
		 * @param name The name of the state.
		 * @param scriptname The name of the script which will be associated with the state.
		 * @return Pointer the new ActorState.
		 * @brief Creates an empty ScriptableActorState and adds it to the Container with the name parameter as key.
		 **/
		ActorState* addState(const char * name, const char * scriptname);

		/**
		 * @param name The name of the state.
		 * @return Pointer to the appropriate ActorState.
		 * @brief Gets the ActorState from the Container which has the name parameter as its key.
		 **/
		ActorState* getState(const char * name);

		/**
		 * @param name The name of the state.
		 * @brief Sets the state which has the parameter name as key as the current state.
		 **/
		void setState(const char * name);

		/**
		 * @param newState Pointer to an ActorState.
		 * @brief Sets the newState as the current state.
		 **/
		void setState(ActorState * newState);

		/**
		 * @param name The name of the sprite.
		 * @return Pointer to a Sprite.
		 * @brief Searches the Container of sprites for the sprite which has the name parameter as its key. Is only used
		 *	      by ActorStates when changing sprites.
		 **/
		Sprite* getSprite(const char * name);

		//////////////////////////////////////////////////////
		// Functions that just call the current state.
		//////////////////////////////////////////////////////

		/**
		 * @return The X position of the actor.
		 * @brief Returns the X position of the current state.
		 **/
		float getX();

		/**
		 * @return The Y position of the actor.
		 * @brief Returns the Y position of the current state.
		 **/
		float getY();

		/**
		 * @return The Z position of the actor.
		 * @brief Returns the Z position of the current state.
		 **/
		float getZ();

		/**
		 * @param x The new X postion.
		 * @brief Sets the X position of the current state.
		 **/
		void setX(float x);

		/**
		 * @param y The new Y postion.
		 * @brief Sets the Y position of the current state.
		 **/
		void setY(float y);

		/**
		 * @param z The new Z postion.
		 * @brief Sets the Z position of the current state.
		 **/
		void setZ(float z);

		/**
		 * @return The position of the actor.
		 * @brief Gets the position of the current state.
		 **/
		Vextor* getPosition();

		/**
		 * @return The X position of the actor.
		 * @brief Returns the X position of the current state.
		 **/
		float getXPosition();

		/**
		 * @return The Y position of the actor.
		 * @brief Returns the Y position of the current state.
		 **/
		float getYPosition();

		/**
		 * @return The Z position of the actor.
		 * @brief Returns the Z position of the current state.
		 **/
		float getZPosition();

		/**
		 * @param newPosition The new position of the actor.
		 * @brief Sets the position of the current state.
		 **/
		void setPosition(Vextor * newPosition);

		/**
		 * @param x The new X postion.
		 * @param y The new Y position.
		 * @brief Sets the position of the current state.
		 **/
		void setPosition(float x, float y);

		/**
		 * @param x The new X postion.
		 * @brief Sets the X position of the current state.
		 **/
		void setXPosition(float x);

		/**
		 * @param y The new Y postion.
		 * @brief Sets the Y position of the current state.
		 **/
		void setYPosition(float y);

		/**
		 * @param z The new Z postion.
		 * @brief Sets the Z position of the current state.
		 **/
		void setZPosition(float z);

		/**
		 * @return The velocity of the actor.
		 * @brief Gets the velocity of the current state.
		 **/
		Vextor* getVelocity();

		/**
		 * @return The X velocity of the actor.
		 * @brief Returns the X velocity of the current state.
		 **/
		float getXVelocity();

		/**
		 * @return The Y velocity of the actor.
		 * @brief Returns the Y velocity of the current state.
		 **/
		float getYVelocity();

		/**
		 * @param newVelocity The new velocity.
		 * @brief Sets the velocity of the current state.
		 **/
		void setVelocity(Vextor * newVelocity);

		/**
		 * @param x The new X velocity.
		 * @param y The new Y velocity.
		 * @brief Sets the velocity of the current state.
		 **/
		void setVelocity(float x, float y);

		/**
		 * @param x The new X velocity.
		 * @brief Sets the X velocity of the current state.
		 **/
		void setXVelocity(float x);

		/**
		 * @param y The new Y velocity.
		 * @brief Sets the Y velocity of the current state.
		 **/
		void setYVelocity(float y);

		/**
		 * @return The acceleration of the actor.
		 * @brief Gets the acceleration of the current state.
		 **/
		Vextor* getAcceleration();

		/**
		 * @return The X acceleration of the actor.
		 * @brief Returns the X acceleration of the current state.
		 **/
		float getXAcceleration();

		/**
		 * @return The Y acceleration of the actor.
		 * @brief Returns the Y acceleration of the current state.
		 **/
		float getYAcceleration();

		/**
		 * @param newAcceleration The new acceleration.
		 * @brief Sets the acceleration of the current state.
		 **/
		void setAcceleration(Vextor * newAcceleration);

		/**
		 * @param x The new X acceleration.
		 * @param y The new Y acceleration.
		 * @brief Sets the acceleration of the current state.
		 **/
		void setAcceleration(float x, float y);

		/**
		 * @param x The new X acceleration.
		 * @brief Sets the X acceleration of the current state.
		 **/
		void setXAcceleration(float x);

		/**
		 * @param y The new Y acceleration.
		 * @brief Sets the Y acceleration of the current state.
		 **/
		void setYAcceleration(float y);

		/**
		 * @return The orientation of the actor.
		 * @brief Gets the orientation of the current state.
		 **/
		float getOrientation();

		/**
		 * @param orientation The new orientation.
		 * @brief Sets the orientation of the current state.
		 **/
		void setOrientation(float orientation);

		/**
		 * @return The current Sprite.
		 * @brief Gets the sprite of the current state.
		 **/
		Sprite* getSprite();

		/**
		 * @param name The name of the sprite.
		 * @brief Sets the sprite of the current state to the Sprite which has the name parameter as its key.
		 **/
		void setSprite(const char * name);

		/**
		 * @param sprite Pointer to a Sprite.
		 * @brief Sets the sprite of the current state to the new Sprite.
		 **/
		void setSprite(Sprite * sprite);

		/**
		 * @brief Initializes all the states in this actor.
		 **/
		void init();

		/**
		 * @param dt Time elapsed in milliseconds.
		 * @brief Updates the current state.
		 **/
		void update(float dt);

		/**
		 * @brief Renders the current state.
		 **/
		void render();

		/**
		 * @brief Loads the current state.
		 **/
		int load();

		/**
		 * @brief Does nothing.
		 **/
		void unload();
	};

	typedef boost::shared_ptr<Actor> pActor;
}

#endif
