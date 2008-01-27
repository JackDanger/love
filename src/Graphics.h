/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_GRAPHICS_H 
#define LOVE_GRAPHICS_H 

// LOVE
#include "Device.h"
#include "Image.h"
#include "Font.h"
#include "Particlesystem.h"
#include "Color.h"
#include "love_align.h"
#include "love_blend.h"


// STD
#include <vector>

namespace love
{

	/**
	* Represents a set of "current" resources. The idea is that
	* classes can push/pop graphics_states.
	**/
	struct graphics_state
	{
		// Back/Foreground color.
		pColor color, background;

		// Current font.
		pFont font;

		// The current blend and color mode.
		int blend_mode, color_mode;
	};

	/**
	* This class serves as an abstraction over graphics contexts.
	* 
	* @author Michael Enger
	* @author Anders Ruud
	* @date 2007-08-26
	**/
	class Graphics : public Device
	{
	protected:

		// The list of graphics states. Note that most
		// of the code assumes that at least one state is
		// available.
		std::vector<graphics_state> states;
		
	public:
	
		Graphics();

		virtual ~Graphics();

		/**
		* Pushes a graphics state.
		**/
		void push();

		/**
		* Pops a graphics state.
		**/
		void pop();

		/**
		* Clears the screen using the background color.
		**/
		virtual void clear() const = 0;

		/**
		* Applies the color as the current color.
		**/
		virtual void apply(const pColor & color) const = 0;

		/**
		* Applies white if color_mode = normal, or the current 
		* color if color_mode = modulate.
		**/
		virtual void cleanColor() const = 0;

		/**
		* Gets the width of the graphics context.
		**/
		int getWidth() const;

		/**
		* Gets the height of the graphics context.
		**/
		int getHeight() const;

		/**
		* Sets the current blend mode.
		**/
		virtual void setBlendMode(int mode);

		/**
		* Gets the current blend mode.
		**/
		int getBlendMode() const;

		/**
		* Sets the current color mode.
		**/
		void setColorMode(int mode);

		/**
		* Gets the current color mode.
		**/
		int getColorMode() const;

		/**
		* Sets the background Color. 
		**/
		void setBackgroundColor(pColor color);
		void setBackgroundColor(int r, int g, int b);

		/**
		* Sets the foreground color.
		**/
		void setColor(pColor color);
		void setColor(int r, int g, int b, int a = 255);

		/**
		* Sets the alpha component of the current color.
		**/
		void setAlpha(int a);

		/**
		* Gets the alpha component of the current color.
		**/
		int getAlpha() const;

		/**
		* Sets the current font.
		**/
		void setFont(pFont font);

		/**
		* Gets an Image object that is compatible with the 
		* current graphics context.
		**/
		virtual pImage newImage(pFile file) const = 0;

		/**
		* Gets a Font object that is compatible with the 
		* current graphics context.
		**/
		virtual pFont newFont(pFile file, int size) const = 0;
		
		/**
		 * Gets an ImageFont object that is compatible with the 
		 * current graphics context.
		 **/
		virtual pFont newImageFont(pFile file, std::string glyphs) const = 0;

		/**
		* Gets a Particlesystem object that is compatible with the 
		* current graphics context.
		**/
		virtual pParticlesystem newParticlesystem() const = 0;

		// Rude wants them here.
		pFont getFont() const;
		pColor getBackgroundColor() const;
		pColor getColor() const;
		
		// Convenience functions. Base source is assumed.
		pImage newImage(const std::string & filename) const;
		pFont newFont(const std::string & filename, int size) const;
		pFont newImageFont(const std::string & filename, const std::string & glyphs) const;

		/**
		* Draw text on screen at the specified coordiantes (automatically breaks \n characters).
		*
		* @param str A string of text.
		* @param x The x-coordiante.
		* @param y The y-coordiante.
		**/
		void draw(const char * str, float x, float y) const;

		/**
		* Draw formatted text on screen at the specified coordinates.
		*
		* @param str A string of text.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		* @param wrap The maximum width of the text area.
		* @param align Where to align the text.
		**/
		void draw(const char * str, float x, float y, int wrap, int align = LOVE_ALIGN_LEFT) const;
		
		/**
		* Draws a line from (x1,y1) to (x2,y2) relative to the point (xpos,ypos).
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param x1 The first relative x-coordinate.
		* @param y1 The first relative y-coordinate.
		* @param x2 The second relative x-coordinate.
		* @param y2 The second relative y-coordinate.
		* @param lineWidth The width of the drawn line.
		**/
		virtual void drawLine(float xpos, float ypos, float x1, float y1, float x2, float y2, float lineWidth = 1) const = 0;
		
		/**
		* Draws a triangle around the point (xpos,ypos) determined from the three relative coordinates.
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param x1 The first relative x-coordinate.
		* @param y1 The first relative y-coordinate.
		* @param x2 The second relative x-coordinate.
		* @param y2 The second relative y-coordinate.
		* @param x3 The third relative x-coordinate.
		* @param y3 The third relative y-coordinate.
		* @param lineWidth The width of the drawn line.
		**/
		virtual void drawTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth = 1) const = 0;
		
		/**
		* Fills a triangle around the point (xpos,ypos) determined from the three relative coordinates.
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param x1 The first relative x-coordinate.
		* @param y1 The first relative y-coordinate.
		* @param x2 The second relative x-coordinate.
		* @param y2 The second relative y-coordinate.
		* @param x3 The third relative x-coordinate.
		* @param y3 The third relative y-coordinate.
		**/
		virtual void fillTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3) const = 0;
		
		/**
		* Draws a quad around the point (xpos,ypos) determined from the four relative coordinates.
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param x1 The first relative x-coordinate.
		* @param y1 The first relative y-coordinate.
		* @param x2 The second relative x-coordinate.
		* @param y2 The second relative y-coordinate.
		* @param x3 The third relative x-coordinate.
		* @param y3 The third relative y-coordinate.
		* @param x4 The fourth relative x-coordinate.
		* @param y4 The fourth relative y-coordinate.
		* @param lineWidth The width of the drawn line.
		**/
		virtual void drawQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth = 1) const = 0;
		
		/**
		* Fills a quad around the point (xpos,ypos) determined from the four relative coordinates.
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param x1 The first relative x-coordinate.
		* @param y1 The first relative y-coordinate.
		* @param x2 The second relative x-coordinate.
		* @param y2 The second relative y-coordinate.
		* @param x3 The third relative x-coordinate.
		* @param y3 The third relative y-coordinate.
		* @param x4 The fourth relative x-coordinate.
		* @param y4 The fourth relative y-coordinate.
		**/
		virtual void fillQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const = 0;
		
		/**
		* Draws a circle around the point (xpos,ypos).
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param radius The radius of the circle.
		* @param points The amount of points to use when drawing the circle.
		* @param lineWidth The width of the drawn line.
		**/
		virtual void drawCircle(float xpos, float ypos, float radius, float points = 10, float lineWidth = 1) const = 0;
		
		/**
		* Fills a circle around the point (xpos,ypos).
		*
		* @param xpos The x-coordinate center of the shape.
		* @param ypos The y-coordinate center of the shape.
		* @param radius The radius of the circle.
		* @param points The amount of points to use when drawing the circle.
		**/
		virtual void fillCircle(float xpos, float ypos, float radius, float points = 10) const = 0;
				
	}; // Graphics
	
} // love

#endif // LOVE_GRAPHICS_H
