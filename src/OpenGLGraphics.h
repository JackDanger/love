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
		* @brief Draws a Bezier curve. 
		* @param bezier The Bezier to draw.
		* @param x The x-coordinate of the position (first point).
		* @param y The y-coordinate of the position (first point).
		* @param precision The amount of points to draw.
		* @param float lineWidth The width of the line used to draw the Bezier.
		**/
		virtual void drawBezier(const pBezier * bezier, float x, float y, int precision = 20, float lineWidth = 2.0f) const;

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
