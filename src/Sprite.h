/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SPRITE_H
#define LOVE_SPRITE_H

// LOVE

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* Sprite is an abstraction over static Images and (non-static) Animations. 
	* It exist so that Images and Animations can be used interchangeably in 
	* other objects.
	*
	* @author Anders Ruud
	* @date 2007-05-18
	**/
	class Sprite
	{
	protected:

		// The width and height of the Sprite. (These are not
		// fixed. Animation, for instance, may change them every frame).
		float width;
		float height;

		// The alpha value for rendering transparencies.
		float alpha;

		// The position of the center. (0, 0) = top left.
		float center_x, center_y;

	public:

		/**
		* Constructs a Sprite with width = 0, height = 0, and alpha = 1.0.
		**/
		Sprite();

		virtual ~Sprite();

		/**
		* Gets the current width of the Sprite. (May change every frame.)
		**/
		float getWidth() const;

		/**
		* Gets the current height of the Sprite. (May change every frame.)
		**/
		float getHeight() const;

		/**
		* Gets the current alpha value.
		**/
		float getAlpha() const;

		/**
		* Sets the current alpha value.
		* @param alpha The new alpha value. Range: 0-1.
		**/
		void setAlpha(float alpha);

		/**
		* Sets the center of the sprite. (The "center").
		**/
		void setCenter(float x, float y);

		/**
		* Binds the hardware texture associated with this Sprite.
		**/
		virtual void bind() const = 0;

		/**
		* Updates the state of the Sprite.
		* @param dt Time since last update.
		**/
		virtual void update(float dt) = 0;

		/**
		* Render the sprite at (0, 0).
		**/
		virtual void render() const = 0;

		/**
		* Render sprite at some position.
		* @param x Position on x-axis.
		* @param y Position on y-axis.
		**/
		virtual void render(float x, float y) const = 0;

		/**
		* Render a subsprite.
		* @param x Position on x-axis.
		* @param y Position on y-axis.
		* @param width The width of the subsprite.
		* @param height The height of the subsprite.
		**/
		virtual void render(float x, float y, float width, float height) const = 0;

		/**
		* Draws the sprite with scale and rotation.
		* @param x Position on x-axis.
		* @param y Position on y-axis.
		* @param angle The angle of the rotation. (0 = normal)
		* @param sx Scaling factor in the x-direction.
		* @param sy Scaling factor in the y-direction.
		**/
		virtual void render(float x, float y, float angle, float sx, float sy) const = 0;

	}; // Sprite

	typedef boost::shared_ptr<Sprite> pSprite;

} // love

#endif // LOVE_SPRITE_H
