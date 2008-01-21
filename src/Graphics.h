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
//#include "Font.h"

#include "love_align.h"

namespace love
{

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

		// Size of graphics context.
		int width, height;

		// Background color.
		pColor background;

		// Foreground color. (Text, primitives.
		pColor color;

		// The current font used for rendering text.
		pFont font;
		
	public:
	
		Graphics();

		virtual ~Graphics();

		/**
		* Clears the screen using the background color.
		**/
		virtual void clear() const = 0;

		/**
		* Applies the color as the current color.
		**/
		virtual void apply(const pColor & color) const = 0;

		/**
		* Gets the width of the graphics context.
		**/
		int getWidth() const;

		/**
		* Gets the height of the graphics context.
		**/
		int getHeight() const;

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
		* Sets the current font.
		**/
		void setFont(pFont font);

		/**
		* Gets an Image object that is compatible with the 
		* current graphics context.
		**/
		virtual pImage getImage(pFile file) const = 0;

		/**
		* Gets a Font object that is compatible with the 
		* current graphics context.
		**/
		virtual pFont getFont(pFile file, int size) const = 0;
		
		/**
		 * Gets an ImageFont object that is compatible with the 
		 * current graphics context.
		 **/
		virtual pFont getImageFont(pFile file, std::string glyphs) const = 0;

		/**
		* Gets a Particlesystem object that is compatible with the 
		* current graphics context.
		**/
		virtual pParticlesystem getParticlesystem() const = 0;

		// Convenience functions. Base source is assumed.
		pImage getImage(const std::string & filename) const;
		pFont getFont(const std::string & filename, int size) const;
		pFont getImageFont(const std::string & filename, std::string glyphs) const;

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
				
	}; // Graphics
	
} // love

#endif // LOVE_GRAPHICS_H
