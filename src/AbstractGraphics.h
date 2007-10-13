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
#include "Font.h"
#include "Bezier.h"

// STL
#include "AbstractDevice.h"

// Boost
#include <boost/shared_ptr.hpp>

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

		// A default font we can revert to in case there is no font selected.
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
		
		/**
		* @brief Sets the current (foreground) color.
		* @param color The new color. 
		* @note The color may or may not be shared with others. (Due to use of shared_ptr).
		**/
		void setColor(const pAbstractColor * color);

		/**
		* @brief Sets the current (foreground) color directly.
		* @param r The red color component, 0-255.
		* @param g The green color component, 0-255.
		* @param b The blue color component, 0-255.
		* @param a The alpha component, 0-255. (Default 255).
		**/
		void setColor(int r, int g, int b, int a = 255);

		/**
		* @brief Sets the background color.
		* @param color The new background color.
		* @note The color may or may not be shared/used by others. ^-^ Using shared_ptr!
		**/
		void setBackground(const pAbstractColor * color);

		/**
		* @brief Sets the background color directly.
		* @param r The red color component, 0-255.
		* @param g The green color component, 0-255.
		* @param b The blue color component, 0-255.
		* @note That's right, no alpha. This is the absolute background color.
		**/
		void setBackground(int r, int g, int b);
		
		/**
		* @brief The current Font used for rendering of text. Used by Lua.
		* @param font The new current Font.
		* @note The Font object may or may not be shared with others.
		**/
		void setFont(const pAbstractFont * font);

		/**
		* @brief The current Font used for rendering of text. Used by LÖVE.
		* @param font The new current Font.
		* @note The Font object may or may not be shared with others.
		**/
		void setFont(pAbstractFont font);

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the current color.
		 **/
		pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the current background color.
		 **/
		pAbstractColor getBackground();

		/**
		 * @return An AbstractFont object.
		 * @brief Returns the current font.
		 **/
		pAbstractFont getFont();

		/**
		* @brief Draws an AbstractImage at the current coordinates.
		* @param sprite The AbstractImage to draw.
		**/
		virtual void drawSprite(const pAbstractImage * sprite) const;

		/**
		* @brief Draws an AbstractImage at the specified coordinates.
		* @param sprite AbstractImage to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @note The method draws the AbstractImage so that its center is at (x,y).
		**/
		virtual void drawSprite(const pAbstractImage * sprite, float x, float y) const;

		/**
		* @brief Draws an AbstractImage at the specified coordinates, scaled to the specified width and height.
		* @param sprite The AbstractImage to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @param width The width to which this AbstractImage should be scaled.
		* @param height The height to which this AbstractImage should scaled.
		* @note The method draws the AbstractImage so that its center is at (x,y).
		**/
		virtual void drawSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const;

		/**
		* @brief Draws an AbstractImage using the specified <b>relative</b> points, at the specified coordinates.
		* @param sprite The AbstractImage to draw.
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
		virtual void drawSprite(const pAbstractImage * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;

		/**
		* @brief Draws a subsprite of an AbstractImage.
		* @param sprite The AbstractImage to render a subsprite from.
		* @param x The x-coordinate of the subsprite. 
		* @param y The y-coordinate of the subsprite.
		* @param width The width of the subsprite.
		* @param height The height of the subsprite.
		**/
		virtual void drawSubSprite(const pAbstractImage * sprite, float x, float y, float width, float height) const;

		/**
		* @brief Draws a FrameAnimation at the current coordinates.
		* @param sprite The FrameAnimation to draw.
		**/
		virtual void drawSprite(const pFrameAnimation * sprite) const;

		/**
		* @brief Draws a FrameAnimation at the specified coordinates.
		* @param sprite FrameAnimation to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @note The method draws the FrameAnimation so that its center is at (x,y).
		**/
		virtual void drawSprite(const pFrameAnimation * sprite, float x, float y) const;

		/**
		* @brief Draws a FrameAnimation at the specified coordinates, scaled to the specified width and height.
		* @param sprite The FrameAnimation to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @param width The width to which this FrameAnimation should be scaled.
		* @param height The height to which this FrameAnimation should scaled.
		* @note The method draws the FrameAnimation so that its center is at (x,y).
		**/
		virtual void drawSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const;

		/**
		* @brief Draws a FrameAnimation using the specified <b>relative</b> points, at the specified coordinates.
		* @param sprite The FrameAnimation to draw.
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
		virtual void drawSprite(const pFrameAnimation * sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;

		/**
		* @brief Draws a subsprite of a FrameAnimation.
		* @param sprite The FrameAnimation to render a subsprite from.
		* @param x The x-coordinate of the subsprite. 
		* @param y The y-coordinate of the subsprite.
		* @param width The width of the subsprite.
		* @param height The height of the subsprite.
		**/
		virtual void drawSubSprite(const pFrameAnimation * sprite, float x, float y, float width, float height) const;

		/**
		* @brief Draws a Sprite at the current coordinates.
		* @param sprite The Sprite to draw.
		**/
		virtual void drawSprite(const pSprite & sprite) const = 0;

		/**
		* @brief Draws a Sprite at the specified coordinates.
		* @param sprite Sprite to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @note The method draws the Sprite so that its center is at (x,y).
		**/
		virtual void drawSprite(const pSprite & sprite, float x, float y) const = 0;

		/**
		* @brief Draws a Sprite at the specified coordinates, scaled to the specified width and height.
		* @param sprite The Sprite to draw.
		* @param x The x-coordinate of the point.
		* @param y The y-coordinate of the point.
		* @param width The width to which this Sprite should be scaled.
		* @param height The height to which this Sprite should scaled.
		* @note The method draws the Sprite so that its center is at (x,y).
		**/
		virtual void drawSprite(const pSprite & sprite, float x, float y, float width, float height) const = 0;

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
		virtual void drawSprite(const pSprite & sprite, float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const = 0;

		/**
		* @brief Draws a subsprite of a Sprite.
		* @param sprite The Sprite to render a subsprite from.
		* @param x The x-coordinate of the subsprite. 
		* @param y The y-coordinate of the subsprite.
		* @param width The width of the subsprite.
		* @param height The height of the subsprite.
		**/
		virtual void drawSubSprite(const pSprite & sprite, float x, float y, float width, float height) const = 0;

		/**
		* @brief Renders a ParticleSystem.
		* @param particleSystem The ParticleSystem to render.
		**/
		virtual void drawParticleSystem(const pParticleSystem * particleSystem) const = 0;

		/**
		* @brief Draws a Bezier curve. 
		* @param bezier The Bezier to draw.
		* @param precision The amount of points to draw.
		* @param float lineWidth The width of the line used to draw the Bezier.
		**/
		virtual void drawBezier(const pBezier * bezier, float x, float y, int precision = 20, float lineWidth = 2.0f) const = 0;

		/**
		* @brief Renders the text string at the specified position.
		* @param str The text to render.
		* @param x The x-coordinate of the position.
		* @param y The y-coordinate of the position.
		**/
		virtual void drawString(const char * str, float x, float y) const = 0;

		/**
		* @brief Draws a formatted string. (Word wrap, line breaks, alignment)
		* @param str The text to render.
		* @param x The x-coordinate of the position of the first character.
		* @param y The y-coordinate of the position of the first character.
		* @param limit Size limit for word wrap.
		* @param align How to align the text.
		**/
		virtual void drawText(const char * str, float x, float y, float limit = 0, int align = 1) const = 0;

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

		
	}; // AbstractGraphics
	
	typedef boost::shared_ptr<AbstractGraphics> pAbstractGraphics;
	
} // love

#endif
