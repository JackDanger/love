#ifndef LOVE_VISUAL_ENTITY_H
#define LOVE_VISUAL_ENTITY_H

#include "Color.h"
#include "Entity.h"
#include "Sprite.h"

namespace love
{
	/**
	* @class VisualEntity
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-05-21
	* @brief An Entity which has a Sprite attached to it and can be seen in the game world.
	**/
	class VisualEntity : public Entity
	{
	protected:
		Color * color;
		Sprite * sprite;

	public:
		/**
		 * @brief Default constructor.
		 **/
		VisualEntity();

		/**
		 * @brief Does nothing.
		 **/
		virtual ~VisualEntity();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void init();

		/**
		 * @return The current Sprite.
		 * @brief Gets the sprite.
		 **/
		Sprite* getSprite();

		/**
		 * @param sprite Pointer to a Sprite.
		 * @brief Sets the sprite of the new Sprite.
		 **/
		virtual void setSprite(Sprite * sprite);

		/**
		 * @param dt Time elapsed in milliseconds.
		 * @brief Updates the sprite and increments velocity with acceleration and position with velocity.
		 **/
		virtual void update(float dt);

		/**
		 * @brief Renders the sprite using the position as center.
		 **/
		virtual void render();

		/**
	 	 * @brief Initializes all the variables as 0.
	 	 **/
		virtual int load();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<VisualEntity> pVisualEntity;
}

#endif
