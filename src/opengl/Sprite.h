/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_SPRITE_H
#define LOVE_OPENGL_SPRITE_H

// LOVE

// Boost
#include <boost/shared_ptr.hpp>

namespace love_opengl
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

		float getCenterX() const;
		float getCenterY() const;

		/**
		* Updates the state of the Sprite.
		* @param dt Time since last update.
		**/
		virtual void update(float dt) = 0;

	}; // Sprite

	typedef boost::shared_ptr<Sprite> pSprite;

} // love

#endif // LOVE_SPRITE_H
