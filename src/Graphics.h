/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright � 2006-2008 LOVE Development Team
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
		* Gets a Particlesystem object that is compatible with the 
		* current graphics context.
		**/
		virtual pParticlesystem getParticlesystem() const = 0;

		// Convenience functions. Base source is assumed.
		pImage getImage(const std::string & filename) const;
		pFont getFont(const std::string & filename, int size) const;

		/**
		* Draw text on screen.
		**/
		void draw(const char * str, float x, float y) const;

		/**
		* Draw formatted text on screen
		**/
		void draw(const char * str, float x, float y, int wrap, int align = LOVE_ALIGN_LEFT) const;
				
	}; // Graphics
	
} // love

#endif // LOVE_GRAPHICS_H
