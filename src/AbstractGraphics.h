/**
* @file AbstractGraphics.h
* @author Anders Ruud
* @date 2007-08-26
* @brief Contains definition for class AbstractGraphics.
**/

#ifndef LOVE_ABSTRACTGRAPHICS_H 
#define LOVE_ABSTRACTGRAPHICS_H 

// LOVE
#include "AbstractImage.h"
#include "FrameAnimation.h"
#include "Sprite.h"
#include "ParticleSystem.h"
#include "AbstractColor.h"
#include "Color.h"
#include "AbstractFont.h"
#include "Text.h"
#include "Bezier.h"
#include "AbstractFile.h"

// STL
#include "AbstractDevice.h"

// Boost
#include <boost/shared_ptr.hpp>

using std::string;
using std::vector;

namespace love
{

	/**
	* @class AbstractGraphics
	* @version 1.0
	* @since 1.0
	* @author Michael Enger & Anders Ruud
	* @date 2007-08-26
	* @brief This class acts as the abstract graphics device.
	* Implementations of it's subclasses contain methods for rendering sprites, text, and so on.
	**/
	class AbstractGraphics : public AbstractDevice
	{
	protected:

		// The color used for rendering text, primitives, and anything that isn't the background.
		pAbstractColor color;

		// The background color.
		pAbstractColor background;

		// The current font used for rendering of text.
		pAbstractFont font;

		// The font used if no font is set.
		pAbstractFont defaultFont;
	
	public:
	
		/**
		* @brief Constructs an empty AbstractGraphics.
		**/
		AbstractGraphics();
		
		/**
		* @brief Destructor.
		**/
		virtual ~AbstractGraphics();
		


		virtual pAbstractImage getImage(pAbstractFile file) const = 0;
		virtual pAbstractFont getFont(pAbstractFile file, int size) const = 0;
		virtual pAbstractFont getImageFont(pAbstractFile file, const string & glyphs) const = 0;

		pAbstractImage getImage(const string & filename) const;
		pAbstractFont getFont(const string & filename, int size) const;
		pAbstractFont getImageFont(const string & filename, const string & glyphs) const;


		/**
		* @brief Sets the current (foreground) color.
		* @param color The new color. 
		* @note The color may or may not be shared with others. (Due to use of shared_ptr).
		**/
		void setColor(const pAbstractColor & color);

		/**
		* @brief Sets the current (foreground) color directly.
		* @param r The red color component, 0-255.
		* @param g The green color component, 0-255.
		* @param b The blue color component, 0-255.
		* @param a The alpha component, 0-255. (Default 255).
		**/
		void setColor(int r, int g, int b, int a = 255);

		/**
		* @brief Sets the current (foreground) color directly.
		* @param code The hexadecimal color code.
		* @param a The alpha component, 0-255. (Default 255).
		**/
		void setColor(int code, int a = 255);

		/**
		* @brief Sets the background color.
		* @param color The new background color.
		* @note The color may or may not be shared/used by others. ^-^ Using shared_ptr!
		**/
		void setBackgroundColor(const pAbstractColor & color);

		/**
		* @brief Sets the background color directly.
		* @param r The red color component, 0-255.
		* @param g The green color component, 0-255.
		* @param b The blue color component, 0-255.
		* @note That's right, no alpha. This is the absolute background color.
		**/
		void setBackgroundColor(int r, int g, int b);

		/**
		* @brief Sets the background color directly.
		* @param code The hexadecimal color code.
		* @note That's right, no alpha. This is the absolute background color.
		**/
		void setBackgroundColor(int code);
		
		/**
		* @brief The current Font used for rendering of text.
		* @param font The new current Font.
		* @note The Font object may or may not be shared with others.
		**/
		void setFont(const pAbstractFont & font);

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the current color.
		 **/
		pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the current background color.
		 **/
		pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractFont object.
		 * @brief Returns the current font.
		 **/
		pAbstractFont getFont();

		/**
		* @brief Sets the alpha for rendering of images.
		* @param a The alpha component, 0-255. (Default 255).
		**/
		virtual void setAlpha(int a = 255) const = 0;

		/**
		* @brief Combines a translation with the current matrix.
		* @param x Translation along x-axis.
		* @param y Translation along y-axis.
		**/
		virtual void translate(float x, float y) const = 0;

		/**
		* @brief Combines a rotation with the current matrix.
		* @param a Amount of rotation (deg).
		**/
		virtual void rotate(float a) const = 0;

		/**
		* @brief Combines a scaling with the current matrix.
		* @param s Scale factor.
		**/
		virtual void scale(float s) const = 0;

		/**
		* @brief Combines a scaling with the current matrix.
		* @param sx Scale factor on x-axis.
		* @param sy Scale factor on y-axis.
		**/
		virtual void scale(float sx, float sy) const = 0;

		/**
		* @brief Draws a sprite at the specified location.
		* @param sprite The sprite to draw.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void draw(const pSprite & sprite, float x = 0, float y = 0) const;

		/**
		* @brief Draws a sub-sprite.
		* @param sprite The sprite to draw.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param xs The x-coordinate within the sprite.
		* @param ys The y-coordinate within the sprite.
		* @param width The width of the sub-sprite.
		* @param height The height of the sub-sprite.
		**/
		virtual void draw(const pSprite & sprite, float x, float y, float xs, float ys, float width, float height) const;

		/**
		* @brief Draws a particle system at the specified location.
		* @param particleSystem The particleSystem to draw.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		virtual void draw(const pParticleSystem & particleSystem, float x = 0, float y = 0) const;

		/**
		* @brief Draws some text at the specified location.
		* @param str A string to draw.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param limit The size limit (for word-wrapping).
		* @param align The alignment (left, right, center).
		**/
		virtual void draw(const string & str, float x = 0, float y = 0, float limit = 0, int align = 1) const;

		/**
		* @brief Draws a line from [x1,y1] to [x2,y2].
		* @param x1 The first x-coordinate.
		* @param y1 The first y-coordinate.
		* @param x2 The second x-coordinate.
		* @param y2 The second y-coordinate.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawLine(float x1, float y1, float x2, float y2, float rotation = 0, float lineWidth = 1) const = 0;

		/**
		* @brief Draws a triangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawTriangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const = 0;

		/**
		* @brief Draws a filled triangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		**/
		virtual void fillTriangle(float x, float y, float width, float height, float rotation = 0) const = 0;

		/**
		* @brief Draws a rectangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawRectangle(float x, float y, float width, float height, float rotation = 0, float lineWidth = 1) const = 0;

		/**
		* @brief Draws a filled rectangle at the coordinate [x,y] with the specified width and height.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param width The width.
		* @param height The height.
		* @param rotation The rotation of the line.
		**/
		virtual void fillRectangle(float x, float y, float width, float height, float rotation = 0) const = 0;

		/**
		* @brief Draws a circle at the coordinate [x,y] with the specified radius.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param radius The radius.
		* @param points The amount of points that make up the circle.
		* @param rotation The rotation of the line.
		* @param lineWidth The width of the line.
		**/
		virtual void drawCircle(float x, float y, float radius, int points = 10, float rotation = 0, float lineWidth = 1) const = 0;

		/**
		* @brief Draws a circle at the coordinate [x,y] with the specified radius.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param radius The radius.
		* @param points The amount of points that make up the circle.
		* @param rotation The rotation of the line.
		**/
		virtual void fillCircle(float x, float y, float radius, int points = 10, float rotation = 0) const = 0;
		
		/**
		* @brief Loads the identity matrix.
		**/
		virtual void identity() const = 0;

		/**
		* @brief Pushes the current matrix onto stack.
		**/
		virtual void push() const = 0;

		/**
		* @brief Pops a matrix of the stack.
		**/
		virtual void pop() const = 0; 

		/**
		* @brief Clears the screen using the background color.
		**/
		virtual void clear() const = 0;
				
	}; // AbstractGraphics
	
	typedef boost::shared_ptr<AbstractGraphics> pAbstractGraphics;
	
} // love

#endif
