#ifndef LOVE_ACTOR_STATE_H
#define LOVE_ACTOR_STATE_H

#include "AbstractState.h"
#include "VisualEntity.h"
#include <boost/shared_ptr.hpp>

namespace love
{
	class Actor;

	/**
	* @class ActorState
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-04-06
	* @brief A non-scriptable state for use with the Actor class.
	**/
	class ActorState : public AbstractState, public VisualEntity
	{
	protected:
		Actor * parent;

	public:
		/**
	 	 * @brief Contructs an empty ActorState.
	 	 **/
		ActorState();

		/**
		 * @param parent The parent Actor.
	 	 * @brief Contructs an empty ActorState and sets the parent actor. This should be used rather than the default constructor.
	 	 **/
		ActorState(Actor * parent);

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual ~ActorState();

		/**
	 	 * @brief For now does nothing.
	 	 **/
		virtual void init();

		/**
		 * @param name The name of the sprite.
		 * @brief Sets the sprite to the Sprite which has the name parameter as its key.
		 **/
		void setSprite(const char * name);

		/**
		 * @param sprite Pointer to a Sprite.
		 * @brief Sets the sprite of the new Sprite.
		 **/
		void setSprite(Sprite * sprite);

		/**
	 	 * @brief Initializes all the variables as 0.
	 	 **/
		virtual int load();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<ActorState> pActorState;
}

#endif
