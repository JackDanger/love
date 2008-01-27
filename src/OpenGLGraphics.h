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
		void applyColorMode() const;
		void setBlendMode(int mode);
		pImage newImage(pFile file) const;
		pFont newFont(pFile file, int size) const;
		pFont newImageFont(pFile file, std::string glyphs) const;
		pParticlesystem newParticlesystem() const;
		void drawLine(float xpos, float ypos, float x1, float y1, float x2, float y2, float lineWidth = 1) const;
		void drawTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float lineWidth = 1) const;
		void fillTriangle(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3) const;
		void drawQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float lineWidth = 1) const;
		void fillQuad(float xpos, float ypos, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;
		void drawCircle(float xpos, float ypos, float radius, float points = 10, float lineWidth = 1) const;
		void fillCircle(float xpos, float ypos, float radius, float points = 10) const;


	}; // OpenGLGraphics
	
} // love

#endif // LOVE_OPENGL_GRAPHICS_H

