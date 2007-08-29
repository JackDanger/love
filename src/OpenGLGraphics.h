/**
* @file OpenGLGraphics.h
* @author Anders Ruud
* @date 2007-08-28
* @brief Contains definition for class OpenGLGraphics.
**/

#ifndef LOVE_OPENGLGRAPHICS_H 
#define LOVE_OPENGLGRAPHICS_H 

// LOVE
#include "AbstractGraphics.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class OpenGLGraphics
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-28
	* @brief 
	**/
	class OpenGLGraphics : public AbstractGraphics
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty OpenGLGraphics.
		**/
		OpenGLGraphics();
		
		/**
		* @brief Destructor.
		**/
		virtual ~OpenGLGraphics();

		/**
		* @brief Inits the graphics.
		* @return LOVE_OK if no errors. 
		**/ 
		virtual int init();

		/**
		* @brief Draws a Sprite at the current coordinates.
		* @param sprite The Sprite to draw.
		**/
		virtual void drawSprite(const pSprite & sprite) const;

		/**
		* @brief Draws a Sprite at the specified coordinates.
		* @param sprite Sprite to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @note The method draws the Sprite so that its center is at (x,y).
		**/
		virtual void drawSprite(const pSprite & sprite, float x, float y) const;

		/**
		* @brief Draws a Sprite at the specified coordinates, scaled to the specified width and height.
		* @param sprite The Sprite to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @param width The width to which this Sprite should be scaled.
		* @param height The height to which this Sprite should scaled.
		* @note The method draws the Sprite so that its center is at (x,y).
		**/
		virtual void drawSprite(const pSprite & sprite, float x, float y, float width, float height) const;

		/**
		* @brief Draws a Sprite using the specified <b>relative</b> points, at the specified coordinates.
		* @param sprite The Sprite to draw.
		* @param x The x-coordinate of the position.
		* @param y The y-coordinate of the position.
		* @param x1 The x-coordinate of the top left corner.
		* @param y1 The y-coordinate of the top left corner.
		* @param x2 The x-coordinate of the bottom left corner.
		* @param y2 The y-coordinate of the bottom left corner.
		* @param x3 The x-coordinate of the bottom right corner.
		* @param y3 The y-coordinate of the bottom right corner.
		* @param x4 The x-coordinate of the top right corner.
		* @param y4 The y-coordinate of the top right corner.
		* @note Remeber that 
		**/
		virtual void drawSprite(const pSprite & sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;

		/**
		* @brief Draws a subsprite of a Sprite.
		* @param sprite The Sprite to render a subsprite from.
		* @param x The x-coordinate of the subsprite. 
		* @param y The y-coordinate of the subsprite.
		* @param width The width of the subsprite.
		* @param height The height of the subsprite.
		**/
		virtual void drawSubSprite(const pSprite & sprite, float x, float y, float width, float height) const;

		/**
		* @brief Renders a ParticleSystem.
		* @param particleSystem The ParticleSystem to render.
		**/
		virtual void drawParticleSystem(const pParticleSystem * particleSystem) const;

		/**
		* @brief Draws a Bezier curve. 
		* @param bezier The Bezier to draw.
		* @param x The x-coordinate of the position (first point).
		* @param y The y-coordinate of the position (first point).
		* @param precision The amount of points to draw.
		* @param float lineWidth The width of the line used to draw the Bezier.
		**/
		virtual void drawBezier(const pBezier * bezier, float x, float y, int precision = 20, float lineWidth = 2.0f) const;

		/**
		* @brief Renders the text string at the specified position.
		* @param str The text to render.
		* @param x The x-coordinate of the position.
		* @param y The y-coordinate of the position.
		**/
		virtual void drawString(const char * str, float x, float y);

		
	}; // OpenGLGraphics
	
	typedef boost::shared_ptr<OpenGLGraphics> pOpenGLGraphics;
	
} // love

#endif
