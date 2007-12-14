/**
* @file LuaGL.h
* @author Anders Ruud
* @date 2007-01-20
* @brief Contains definition for class LuaGL.
**/

#ifndef LOVE_LUAGL_H
#define LOVE_LUAGL_H

// LOVE
#include "Color.h"
#include "Object.h"

// STL
#include <map>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class LuaGL
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-01-20
	* @brief 
	**/
	class LuaGL : public Object
	{
	private:

		std::map<std::string, int> globals;

	public:

		/**
		* @brief Contructs an empty LuaGL.
		**/
		LuaGL();
		virtual ~LuaGL();

		void translate(float x, float y);
		void rotate(float alpha);
		void rotate(float alpha, float x, float y, float z);
		void scale(float sx, float sy);

		void loadIdentity();
		void pushMatrix();
		void popMatrix();

		void begin(const char * str);
		void finish();

		void vertex(float x, float y);
		void texCoord(float s, float t);

		void color(int r, int g, int b, int a = 255);
		void color(Color * color);

		void enable(const char * str);
		void disable(const char * str);

		void hint(const char * target, const char * mode);

		void shadeModel(const char * str);

		void blendFunc(const char * source, const char * destination);

		// Special blend func shortcuts
		void blendFuncNormal();
		void blendFuncAdditive();

		void alphaFunc(const char * func , float ref);

		void clear(const char * str);



	};

	typedef boost::shared_ptr<LuaGL> pLuaGL;

} // love

#endif

