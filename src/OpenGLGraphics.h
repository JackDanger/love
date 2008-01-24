/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_GRAPHICS_H 
#define LOVE_OPENGL_GRAPHICS_H 

// LOVE
#include "Graphics.h"

namespace love
{

	/**
	* Implementation of an OpenGL graphics context.
	*
	* @author Anders Ruud
	* @date 2007-08-28
	**/
	class OpenGLGraphics : public Graphics
	{
	private:
	public:
	
		/**
		* Constructs an empty OpenGLGraphics.
		**/
		OpenGLGraphics();
		
		virtual ~OpenGLGraphics();

		// From Device.
		bool init(int argc, char* argv[]);
		void quit();

		// From Graphics.
		void clear() const;
		void apply(const pColor & color) const;
		pImage newImage(pFile file) const;
		pFont newFont(pFile file, int size) const;
		pFont newImageFont(pFile file, std::string glyphs) const;
		pParticlesystem newParticlesystem() const;
		// Remember to remove it here too
		void drawRectangle(float x, float y, float width, float height) const;


	}; // OpenGLGraphics
	
} // love

#endif // LOVE_OPENGL_GRAPHICS_H

