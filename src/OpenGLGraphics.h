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
		* @brief Renders a ParticleSystem at a given position. The position defined in the 
		* object is ignored.
		* @param particleSystem The ParticleSystem to render.
		* @param x The x-coordinate of the position.
		* @param y The y-coordinate of the position.
		**/
		virtual void drawParticleSystem(const pParticleSystem * particleSystem, float x, float y) const;

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
		virtual void drawString(const char * str, float x, float y) const;
		
		/**
		* @brief Draws a formatted string. (Word wrap, line breaks, alignment)
		* @param str The text to render.
		* @param x The x-coordinate of the position of the first character.
		* @param y The y-coordinate of the position of the first character.
		* @param limit Size limit for word wrap.
		* @param align How to align the text.
		**/
		virtual void drawText(const char * str, float x, float y, float limit = 0, int align = 1) const;

		/**
		* @brief Combines a translation with the current matrix.
		* @param x Translation along x-axis.
		* @param y Translation along y-axis.
		**/
		virtual void translate(float x, float y) const;

		/**
		* @brief Combines a rotation with the current matrix.
		* @param a Amount of rotation (deg).
		**/
		virtual void rotate(float a) const;

		/**
		* @brief Combines a scaling with the current matrix.
		* @param s Scale factor.
		**/
		virtual void scale(float s) const;

		/**
		* @brief Combines a scaling with the current matrix.
		* @param sx Scale factor on x-axis.
		* @param sy Scale factor on y-axis.
		**/
		virtual void scale(float sx, float sy) const;
		
		/**
		* @brief Loads the identity matrix.
		**/
		virtual void identity() const;

		/**
		* @brief Pushes the current matrix onto stack.
		**/
		virtual void push() const;

		/**
		* @brief Pops a matrix of the stack.
		**/
		virtual void pop() const; 

		/**
		* @brief Clears the screen using the background color.
		**/
		virtual void clear() const;

		/**
		* @brief Draws a line from [x1,y1] to [x2,y2].
		* @param x1 The first x-coordinate.
		* @param y1 The first y-coordinate.
		* @param x2 The second x-coordinate.
		* @param y2 The second y-coordinate.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawLine(float x1, float y1, float x2, float y2, float rotation = 0, float lineWidth = 1) const;

		/**
		* @brief Draws a triangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawTriangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const;

		/**
		* @brief Draws a filled triangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		**/
		virtual void fillTriangle(float x, float y, float width, float height, float rotation = 0) const;

		/**
		* @brief Draws a rectangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawRectangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const;

		/**
		* @brief Draws a filled rectangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		**/
		virtual void fillRectangle(float x, float y, float width, float height, float rotation = 0) const;

		/**
		* @brief Draws a circle at the coordinate [x,y] with the specified radius.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param radius The radius.
		* @param points The amount of points that make up the circle.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawCircle(float x, float y, float radius, int points = 10, float rotation = 0, float lineWidth = 1) const;

		/**
		* @brief Draws a circle at the coordinate [x,y] with the specified radius.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param radius The radius.
		* @param points The amount of points that make up the circle.
		* @param rotation The rotation of the line.
		**/
		virtual void fillCircle(float x, float y, float radius, int points = 10, float rotation = 0) const;
	}; // OpenGLGraphics
	
	typedef boost::shared_ptr<OpenGLGraphics> pOpenGLGraphics;
	
} // love

#endif
