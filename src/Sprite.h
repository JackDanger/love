/**
* @file Sprite.h
* @author Anders Ruud
* @date 2006-10-26
* @brief Contains definition for class Sprite.
**/

#ifndef LOVE_SPRITE_H
#define LOVE_SPRITE_H

// LOVE
#include "AbstractEntity.h"
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	typedef struct
	{
		float xTex;
		float yTex;
		float wTex;
		float hTex;

		float width;
		float height;

		// Distance to center of sprite.
		float top;
		float left;

	} renderinfo;


	/**
	* @class Sprite
	* @version 1.0
	* @since 1.0
	* @author 
	* @date 2007-05-18
	* @brief 
	**/
	class Sprite : public AbstractEntity, public Loadable
	{
	protected:

		float width;
		float height;

		// The alpha value for rendering transparencies.
		float alpha;

	public:

		/**
		* @brief Contructs an empty Sprite.
		**/
		Sprite();
		virtual ~Sprite();

		/**
		* @brief Gets the current width of the Sprite. (May change every frame.)
		* @return The current width of the Sprite.
		**/
		float getWidth() const;

		/**
		* @brief Gets the current height of the Sprite. (May change every frame.)
		* @return The current height of the Sprite.
		**/
		float getHeight() const;

		/**
		* @brief Gets the current alpha value.
		* @return The current alpha value.
		**/
		float getAlpha() const;

		/**
		* @brief Sets the current alpha value.
		* @param alpha The new alpha value.
		**/
		void setAlpha(float alpha);

		// For "performance" rendering
		virtual void bind();
		virtual void beginRender();
		virtual void sendVertices();
		virtual void endRender();

		virtual renderinfo getRenderInfo() = 0;
		virtual renderinfo getRenderInfo(float x, float y, float width, float height) = 0;
		
		virtual void render();

		virtual void render(float x, float y);
		
		/**
		* @brief Renders sprite onto the the quad given by the vertices.
		* Vertices must be in counter clockwise order.
		*
		* @param x1 X-coordinate of first point.
		* @param y1 Y-coordinate of first point.
		* @param x2 X-coordinate of second point.
		* @param y2 Y-coordinate of second point.
		* @param x3 X-coordinate of third point.
		* @param y3 Y-coordinate of third point.
		* @param x4 X-coordinate of fourth point.
		* @param y4 Y-coordinate of fourth point.
		**/
		virtual void renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

		/**
		* @brief Render only part of the sprite.
		* @param x X-coordinate of the top-left corner.
		* @param y Y-coordinate of the top-left corner.
		* @param width The width of the rendered area.
		* @param height The height of the rendered area.
		**/
		virtual void render(float x, float y, float width, float height);


	};

	typedef boost::shared_ptr<Sprite> pSprite;

} // love

#endif
