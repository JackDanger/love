/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "Frame.h"
#include <common/Matrix.h>

// STD
#include <cstring> // For memcpy

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace graphics
{
namespace opengl
{
	Frame::Frame(Image *image, int x, int y, int w, int h)
	{
		image->retain();
		this->image = image;
		memset(vertices, 255, sizeof(vertex)*4);
		float iw = image->getWidth();
		float ih = image->getHeight();
		
		vertices[0].x = 0; vertices[0].y = 0;
		vertices[1].x = 0; vertices[1].y = (float)h;
		vertices[2].x = (float)w; vertices[2].y = (float)h;
		vertices[3].x = (float)w; vertices[3].y = 0;
		
		vertices[0].s = x/iw; vertices[0].t = y/ih;
		vertices[1].s = x/iw; vertices[1].t = (y+h)/ih;
		vertices[2].s = (x+w)/iw; vertices[2].t = (y+h)/ih;
		vertices[3].s = (x+w)/iw; vertices[3].t = y/ih;
	}
	
	Frame::~Frame()
	{
		if (image != 0)
			image->release();
	}
	
	void Frame::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		//shameless ripoff of Image
		static Matrix transform;

		image->bind();

		glPushMatrix();

		transform.setTransformation(x, y, angle, sx, sy, ox, oy);
		glMultMatrixf((const GLfloat*)transform.getElements());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&vertices[0].x);
		glTexCoordPointer(2, GL_FLOAT, sizeof(vertex), (GLvoid*)&vertices[0].s);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glPopMatrix();
	}
	
	void Frame::flip(bool x, bool y)
	{
		vertex temp[4];
		if (x)
		{
			memcpy(temp, vertices, sizeof(vertex)*4);
			vertices[0].s = temp[3].s; vertices[0].t = temp[3].t;
			vertices[1].s = temp[2].s; vertices[1].t = temp[2].t;
			vertices[2].s = temp[1].s; vertices[2].t = temp[1].t;
			vertices[3].s = temp[0].s; vertices[3].t = temp[0].t;
		}
		if (y)
		{
			memcpy(temp, vertices, sizeof(vertex)*4);
			vertices[0].s = temp[1].s; vertices[0].t = temp[1].t;
			vertices[1].s = temp[0].s; vertices[1].t = temp[0].t;
			vertices[2].s = temp[3].s; vertices[2].t = temp[3].t;
			vertices[3].s = temp[2].s; vertices[3].t = temp[2].t;
		}
	}
} // opengl
} // graphics
} // love
