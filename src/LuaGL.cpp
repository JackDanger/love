#include "LuaGL.h"
#include "love_gl.h"

namespace love
{

	LuaGL::LuaGL()
	{
		
		setType(LOVE_TYPE_LUAGL);

		// Shapes
		globals["POINTS"]			= GL_POINTS;
		globals["LINES"]			= GL_LINES;
		globals["LINE_LOOP"]		= GL_LINE_LOOP;
		globals["LINE_STRIP"]		= GL_LINE_STRIP;
		globals["TRIANGLES"]		= GL_TRIANGLES;
		globals["TRIANGLE_STRIP"]	= GL_TRIANGLE_STRIP;
		globals["TRIANGLE_FAN"]		= GL_TRIANGLE_FAN;
		globals["QUADS"]			= GL_QUADS;
		globals["QUAD_STRIP"]		= GL_QUAD_STRIP;
		globals["POLYGON"]			= GL_POLYGON;

		// Enable/disable
		globals["TEXTURE"]			= GL_TEXTURE_2D;	
		globals["LINE_SMOOTH"]		= GL_LINE_SMOOTH;
		globals["POLYGON_SMOOTH"]	= GL_POLYGON_SMOOTH;
		globals["DEPTH_TEST"]			= GL_DEPTH_TEST;
		globals["ALPHA_TEST"]			= GL_ALPHA_TEST;
		globals["MULTISAMPLE"]			= GL_MULTISAMPLE;

		// Hint targets
		globals["PERSPECTIVE_CORRECTION_HINT"]	= GL_PERSPECTIVE_CORRECTION_HINT;
		globals["POINT_SMOOTH_HINT"]				= GL_POINT_SMOOTH_HINT;
		globals["LINE_SMOOTH_HINT"]				= GL_LINE_SMOOTH_HINT;
		globals["POLYGON_SMOOTH_HINT"]			= GL_POLYGON_SMOOTH_HINT;
		globals["FOG_HINT"]						= GL_FOG_HINT;

		// Hint modes
		globals["DONT_CARE"]	= GL_DONT_CARE;
		globals["FASTEST"]		= GL_FASTEST;
		globals["NICEST"]		= GL_NICEST;

		// Shade modes
		globals["FLAT"]		= GL_FLAT;
		globals["SMOOTH"]	= GL_SMOOTH;

		/* BlendingFactorDest */
		globals["ZERO"] = GL_ZERO;
		globals["ONE"] = GL_ONE;
		globals["SRC_COLOR"] = GL_SRC_COLOR;
		globals["ONE_MINUS_SRC_COLOR"] = GL_ONE_MINUS_SRC_COLOR;
		globals["SRC_ALPHA"] = GL_SRC_ALPHA;
		globals["ONE_MINUS_SRC_ALPHA"] = GL_ONE_MINUS_SRC_ALPHA;
		globals["DST_ALPHA"] = GL_DST_ALPHA;
		globals["ONE_MINUS_DST_ALPHA"] = GL_ONE_MINUS_DST_ALPHA;

		/* BlendingFactorSrc */
		/*      GL_ZERO */
		/*      GL_ONE */
		globals["DST_COLOR"] = GL_DST_COLOR;
		globals["ONE_MINUS_DST_COLOR"] = GL_ONE_MINUS_DST_COLOR;
		globals["SRC_ALPHA_SATURATE"] = GL_SRC_ALPHA_SATURATE;
		/*      GL_SRC_ALPHA */
		/*      GL_ONE_MINUS_SRC_ALPHA */
		/*      GL_DST_ALPHA */
		/*      GL_ONE_MINUS_DST_ALPHA */

		globals["NEVER"] = GL_NEVER;
		globals["ALWAYS"] = GL_ALWAYS;
		globals["LESS"] = GL_LESS;
		globals["LEQUAL"] = GL_LEQUAL;
		globals["EQUAL"] = GL_EQUAL;
		globals["GEQUAL"] = GL_GEQUAL;
		globals["GREATER"] = GL_GREATER;
		globals["NOTEQUAL"] = GL_NOTEQUAL;

		globals["COLOR_BUFFER_BIT"] = GL_COLOR_BUFFER_BIT;
		globals["DEPTH_BUFFER_BIT"] = GL_DEPTH_BUFFER_BIT;


		


	}

	LuaGL::~LuaGL()
	{
	}

	void LuaGL::translate(float x, float y)
	{
		glTranslatef(x, y, 0);
	}

	void LuaGL::rotate(float alpha)
	{
		glRotatef(alpha, 0, 0, 1);
	}

	void LuaGL::rotate(float alpha, float x, float y, float z)
	{
		glRotatef(alpha, x, y, z);
	}

	void LuaGL::scale(float sx, float sy)
	{
		glScalef(sx, sy, 0);
	}

	void LuaGL::loadIdentity()
	{
		glLoadIdentity();
	}

	void LuaGL::pushMatrix()
	{
		glPushMatrix();
	}

	void LuaGL::popMatrix()
	{
		glPopMatrix();
	}


	void LuaGL::begin(const char * str)
	{
		glBegin(globals[str]);
	}

	void LuaGL::finish()
	{
		glEnd();
	}

	void LuaGL::vertex(float x, float y)
	{
		glVertex2f(x, y);
	}

	void LuaGL::texCoord(float s, float t)
	{
		glTexCoord2f(s, t);
	}

	void LuaGL::color(int r, int g, int b, int a)
	{
		glColor4ub(r, g, b, a);
	}

	void LuaGL::color(Color * color)
	{
		glColor4ub(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha());
	}

	void LuaGL::enable(const char * str)
	{
		glEnable(globals[str]);
	}

	void LuaGL::disable(const char * str)
	{
		glDisable(globals[str]);
	}

	void LuaGL::hint(const char * target, const char * mode)
	{
		glHint(globals[target], globals[mode]);
	}

	void LuaGL::shadeModel(const char * str)
	{
		glShadeModel(globals[str]);
	}

	void LuaGL::blendFunc(const char * source, const char * destination)
	{
		glBlendFunc(globals[source], globals[destination]);
	}

	void LuaGL::blendFuncNormal()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void LuaGL::blendFuncAdditive()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}

	void LuaGL::alphaFunc(const char * func , float ref)
	{
		glAlphaFunc(globals[func], ref);
	}

	void LuaGL::clear(const char * str)
	{
		glClear(globals[str]);
	}


}// love
