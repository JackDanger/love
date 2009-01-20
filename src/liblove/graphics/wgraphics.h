/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_GRAPHICS_W
#define LOVE_GRAPHICS_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wColor.h"
#include "wFont.h"
#include "wDrawable.h"
#include "wImage.h"
//#include "wAnimation.h"
#include "wParticleSystem.h"
#include "wSpriteBatch.h"
#include "wVertexBuffer.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{

	int _wrap_checkMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_toboolean(L, 3);
		luax_pushboolean(L, checkMode(w, h, fs));
		return 1;
	}

	int _wrap_setMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_optboolean(L, 3, false);
		bool vsync = luax_optboolean(L, 4, true);
		int fsaa = luaL_optint(L, 5, 0);
		luax_pushboolean(L, setMode(w, h, fs, vsync, fsaa));
		return 1;
	}

	int _wrap_toggleFullscreen(lua_State * L)
	{
		luax_pushboolean(L, toggleFullscreen());
		return 1;
	}

	int _wrap_reset(lua_State * L)
	{
		reset();
		return 0;
	}

	int _wrap_clear(lua_State * L)
	{
		clear();
		return 0;
	}

	int _wrap_present(lua_State * L)
	{
		present();
		return 0;
	}

	int _wrap_setCaption(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		setCaption(str);
		return 0;
	}

	// int getCaption(lua_State * L);

	int _wrap_getWidth(lua_State * L)
	{
		lua_pushnumber(L, getWidth());
		return 1;
	}

	int _wrap_getHeight(lua_State * L)
	{
		lua_pushnumber(L, getHeight());
		return 1;
	}

	int _wrap_isCreated(lua_State * L)
	{
		luax_pushboolean(L, isCreated());
		return 1;
	}

	int _wrap_setScissor(lua_State * L)
	{
		if(lua_gettop(L) == 0)
		{
			setScissor();
			return 0;
		}
	
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		int w = luaL_checkint(L, 3);
		int h = luaL_checkint(L, 4);

		setScissor(x, y, w, h);
		return 0;
	}

	// int getScissor(lua_State * L);

	int _wrap_newColor(lua_State * L)
	{
		int r = luaL_checkinteger(L, 1);
		int g = luaL_checkinteger(L, 2);
		int b = luaL_checkinteger(L, 3);
		int a = luaL_optint(L, 4, 255);

		Color * t = newColor(r, g, b, a);

		luax_newtype(L, "Color", LOVE_WRAP_COLOR_BITS, (void*)t);

		return 1;
	}

	int _wrap_newImage(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to ImageData, if necessary.
		if(luax_istype(L, 1, LOVE_FILE_BITS))
			luax_convobj(L, 1, "image", "newImageData");

		ImageData * data = luax_checktype<ImageData>(L, 1, "ImageData", LOVE_IMAGE_DATA_BITS);

		// Create the image.
		Image * image = newImage(data);
			
		if(image == 0)
			return luaL_error(L, "Could not load image.");


		// Push the type.
		luax_newtype(L, "Image", LOVE_WRAP_IMAGE_BITS, (void*)image);

		return 1;
	}

	int _wrap_newFont(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Check the value.
		File * file = luax_checktype<File>(L, 1, "File", LOVE_FILE_BITS);

		// Second optional parameter can be a number:
		int size = luaL_optint(L, 2, 12);

		Font * font = newFont(file, size);

		if(font == 0)
			return luaL_error(L, "Could not load the font");
		
		luax_newtype(L, "Font", LOVE_WRAP_FONT_BITS, (void*)font);
		
		return 1;
	}

	/*
	int _wrap_newAnimation(lua_State * L)
	{
		// If string, then convert to file.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to ImageData, if necessary.
		if(luax_istype(L, 1, LOVE_FILE_BITS))
			luax_convobj(L, 1, "image", "newImageData");

		// If file, then convert to image.
		if(luax_istype(L, 1, LOVE_IMAGE_DATA_BITS))
		{
			ImageData * data = luax_checktype<ImageData>(L, 1, "ImageData", LOVE_IMAGE_DATA_BITS);
			Image * image = newImage(data);
			luax_newtype(L, "Image", LOVE_WRAP_IMAGE_BITS, (void*)image);
			lua_replace(L, 1);
		}

		// Check the value.
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_WRAP_IMAGE_BITS);

		Animation * animation = 0;

		if(lua_gettop(L) == 1)
		{
			animation = newAnimation(image);
		}
		else 
		{
			float fw = (float)luaL_checknumber(L, 2);
			float fh = (float)luaL_checknumber(L, 3);
			float delay = (float)luaL_checknumber(L, 4);
			int num = luaL_optint(L, 5, 0);
			animation = newAnimation(image, fw, fh, delay, num);
		}

		if(animation == 0)
			return luaL_error(L, "Could not load the Animation");
		
		luax_newtype(L, "Animation", LOVE_WRAP_ANIMATION_BITS, (void*)animation);
		return 1;
	}
	*/

	int _wrap_newSpriteBatch(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_WRAP_IMAGE_BITS);
		int size = luaL_optint(L, 2, 1000);
		int usage = luaL_optint(L, 3, USAGE_ARRAY);
		SpriteBatch * t = newSpriteBatch(image, size, usage);
		luax_newtype(L, "SpriteBatch", LOVE_WRAP_SPRITE_BATCH_BITS, (void*)t);
		return 1;
	}

	int _wrap_newVertexBuffer(lua_State * L)
	{

		Image * image;
		int type, usage, size;

		if(luax_istype(L, 1, LOVE_WRAP_IMAGE_BITS))
		{
			image = luax_checktype<Image>(L, 1, "Image", LOVE_WRAP_IMAGE_BITS);
			size = luaL_optint(L, 2, 100);
			type = luaL_optint(L, 3, TYPE_TRIANGLES);
			usage = luaL_optint(L, 4, USAGE_ARRAY);
		}
		else if(lua_isnumber(L, 1))
		{
			image = 0;
			size = luaL_optint(L, 1, 100);
			type = luaL_optint(L, 2, TYPE_TRIANGLES);
			usage = luaL_optint(L, 3, USAGE_ARRAY);
		}
		else return luaL_error(L, "Expected type image or number");

		VertexBuffer * t = newVertexBuffer(image, size, type, usage);
		luax_newtype(L, "VertexBuffer", LOVE_WRAP_VERTEX_BUFFER_BITS, (void*)t);
		return 1;
	}

	int _wrap_setColor(lua_State * L)
	{
		if(luax_istype(L, 1, LOVE_WRAP_COLOR_BITS))
		{
			Color * color = luax_checktype<Color>(L, 1, "Color", LOVE_WRAP_COLOR_BITS);
			setColor(color);
			return 0;
		}

		int r = luaL_checkint(L, 1);
		int g = luaL_checkint(L, 2);
		int b = luaL_checkint(L, 3);
		int a = luaL_optint(L, 4, 255);

		setColor(r, g, b, a);

		return 1;
	}

	int _wrap_getColor(lua_State * L)
	{
		Color * color = getColor();
		luax_newtype(L, "Color", LOVE_WRAP_COLOR_BITS, (void*)color);
		return 1;
	}

	int _wrap_setBackgroundColor(lua_State * L)
	{
		if(luax_istype(L, 1, LOVE_WRAP_COLOR_BITS))
		{
			Color * color = luax_checktype<Color>(L, 1, "Color", LOVE_WRAP_COLOR_BITS);
			setBackgroundColor(color);
			return 0;
		}

		int r = luaL_checkint(L, 1);
		int g = luaL_checkint(L, 1);
		int b = luaL_checkint(L, 1);

		setBackgroundColor(r, g, b);

		return 1;
	}

	int _wrap_getBackgroundColor(lua_State * L)
	{
		Color * color = getBackgroundColor();
		luax_newtype(L, "Color", LOVE_WRAP_COLOR_BITS, (void*)color);
		return 1;
	}

	int _wrap_setFont(lua_State * L)
	{
		// The second parameter is an optional int.
		int size = luaL_optint(L, 2, 12);

		// If the first parameter is a string, convert it to a file.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// If the first parameter is a File, use another setFont function.
		if(luax_istype(L, 1, LOVE_FILE_BITS))
		{
			File * file = luax_checktype<File>(L, 1, "File", LOVE_FILE_BITS);
			setFont(file, size);
			return 0;
		}

		Font * font = luax_checktype<Font>(L, 1, "Font", LOVE_WRAP_FONT_BITS);
		setFont(font);
		return 0;
	}

	int _wrap_getFont(lua_State * L)
	{
		Font * f = getFont();

		if(f == 0)
			return 0;

		f->retain();
		luax_newtype(L, "Font", LOVE_WRAP_FONT_BITS, (void*)f);
		return 1;
	}

	int _wrap_setBlendMode(lua_State * L)
	{
		int mode = luaL_checkint(L, 1);
		setBlendMode(mode);
		return 0;
	}

	int _wrap_setColorMode(lua_State * L)
	{
		int mode = luaL_checkint(L, 1);
		setColorMode(mode);
		return 0;
	}

	int _wrap_getBlendMode(lua_State * L)
	{
		lua_pushinteger(L, getBlendMode());
		return 1;
	}

	int _wrap_getColorMode(lua_State * L)
	{
		lua_pushinteger(L, getColorMode());
		return 1;
	}

	int _wrap_setLineWidth(lua_State * L)
	{
		float width = (float)luaL_checknumber(L, 1);
		setLineWidth(width);
		return 0;
	}

	int _wrap_setLineStyle(lua_State * L)
	{
		int style = luaL_checkint(L, 1);
		setLineStyle(style);
		return 0;
	}

	int _wrap_setLine(lua_State * L)
	{
		float width = (float)luaL_checknumber(L, 1);
		int style = luaL_optint(L, 2, LINE_SMOOTH);
		setLine(width, style);
		return 0;
	}

	int _wrap_setLineStipple(lua_State * L)
	{
		if(lua_gettop(L) == 0)
		{
			setLineStipple();
			return 0;
		}

		unsigned short pattern = (unsigned short)luaL_checkint(L, 1);
		int repeat = luaL_optint(L, 2, 1);
		setLineStipple(pattern, repeat);
		return 0;
	}

	int _wrap_getLineWidth(lua_State * L)
	{
		lua_pushnumber(L, getLineWidth());
		return 1;
	}

	int _wrap_getLineStyle(lua_State * L)
	{
		lua_pushinteger(L, getLineStyle());
		return 1;
	}

	// getLineStipple

	int _wrap_setPointSize(lua_State * L)
	{
		float size = (float)luaL_checknumber(L, 1);
		setPointSize(size);
		return 0;
	}

	int _wrap_setPointStyle(lua_State * L)
	{
		int style = luaL_checkint(L, 1);
		setPointStyle(style);
		return 0;
	}

	int _wrap_setPoint(lua_State * L)
	{
		float size = (float)luaL_checknumber(L, 1);
		int style = luaL_optint(L, 2, POINT_SMOOTH);
		setPoint(size, style);
		return 0;
	}

	int _wrap_getPointSize(lua_State * L)
	{
		lua_pushnumber(L, getPointSize());
		return 1;
	}

	int _wrap_getPointStyle(lua_State * L)
	{
		lua_pushinteger(L, getPointStyle());
		return 1;
	}

	int _wrap_getMaxPointSize(lua_State * L)
	{
		lua_pushnumber(L, getMaxPointSize());
		return 1;
	}

	/**
	* Draws an Image at the specified coordinates, with rotation and 
	* scaling along both axes.
	* @param x The x-coordinate.
	* @param y The y-coordinate.
	* @param angle The amount of rotation.
	* @param sx The scale factor along the x-axis. (1 = normal).
	* @param sy The scale factor along the y-axis. (1 = normal).
	* @param ox The offset along the x-axis.
	* @param oy The offset along the y-axis.
	**/
	int _wrap_draw(lua_State * L)
	{
		Drawable * drawable = luax_checktype<Drawable>(L, 1, "Drawable", LOVE_DRAWABLE_BITS);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		drawable->draw(x, y, angle, sx, sy, ox, oy);
		return 0;
	}

	int _wrap_drawTest(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_WRAP_IMAGE_BITS);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		drawTest(image, x, y, angle, sx, sy, ox, oy);
		return 0;
	}

	int _wrap_print(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);

		switch(lua_gettop(L))
		{
		case 3:
			print(str, x, y);
			break;
		case 4:
			print(str, x, y, angle);
			break;
		case 5:
			print(str, x, y, angle, sx);
			break;
		case 6:
			print(str, x, y, angle, sx, sy);
			break;
		default:
			return luaL_error(L, "Incorrect number of parameters");
		}
		return 0;
	}

	int _wrap_printf(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float wrap = (float)luaL_checknumber(L, 4);
		int align = luaL_optint(L, 5, 0);
		love::LOVE_WRAP_NAMESPACE::printf(str, x, y, wrap, align);
		return 0;
	}

	int _wrap_point(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		point(x, y);
		return 0;
	}

	int _wrap_line(lua_State * L)
	{
		float x1 = (float)luaL_checknumber(L, 1);
		float y1 = (float)luaL_checknumber(L, 2);
		float x2 = (float)luaL_checknumber(L, 3);
		float y2 = (float)luaL_checknumber(L, 4);
		line(x1, y1, x2, y2);
		return 0;
	}

	int _wrap_triangle(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x1 = (float)luaL_checknumber(L, 2);
		float y1 = (float)luaL_checknumber(L, 3);
		float x2 = (float)luaL_checknumber(L, 4);
		float y2 = (float)luaL_checknumber(L, 5);
		float x3 = (float)luaL_checknumber(L, 6);
		float y3 = (float)luaL_checknumber(L, 7);
		triangle(type, x1, y1, x2, y2, x3, y3);
		return 0;
	}

	int _wrap_rectangle(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float w = (float)luaL_checknumber(L, 4);
		float h = (float)luaL_checknumber(L, 5);
		rectangle(type, x, y, w, h);
		return 0;
	}

	int _wrap_quad(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x1 = (float)luaL_checknumber(L, 2);
		float y1 = (float)luaL_checknumber(L, 3);
		float x2 = (float)luaL_checknumber(L, 4);
		float y2 = (float)luaL_checknumber(L, 5);
		float x3 = (float)luaL_checknumber(L, 6);
		float y3 = (float)luaL_checknumber(L, 7);
		float x4 = (float)luaL_checknumber(L, 6);
		float y4 = (float)luaL_checknumber(L, 7);
		quad(type, x1, y1, x2, y2, x3, y3, x4, y4);
		return 0;
	}

	int _wrap_circle(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float radius = (float)luaL_checknumber(L, 4);
		int points = luaL_optint(L, 5, 10);
		circle(type, x, y, radius, points);
		return 0;
	}

	int _wrap_push(lua_State * L)
	{
		push();
		return 0;
	}

	int _wrap_pop(lua_State * L)
	{
		pop();
		return 0;
	}

	int _wrap_rotate(lua_State * L)
	{
		float deg = (float)luaL_checknumber(L, 1);
		rotate(deg);
		return 0;
	}

	int _wrap_scale(lua_State * L)
	{
		float sx = (float)luaL_optnumber(L, 1, 1.0f);
		float sy = (float)luaL_optnumber(L, 2, sx);
		scale(sx, sy);
		return 0;
	}

	int _wrap_translate(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		translate(x, y);
		return 0;
	}

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
		{ "checkMode", _wrap_checkMode },
		{ "setMode", _wrap_setMode },
		{ "toggleFullscreen", _wrap_toggleFullscreen },
		{ "reset", _wrap_reset },
		{ "clear", _wrap_clear },
		{ "present", _wrap_present },

		{ "newColor", _wrap_newColor },
		{ "newImage", _wrap_newImage },
		{ "newFont", _wrap_newFont },
		{ "newSpriteBatch", _wrap_newSpriteBatch },
		{ "newVertexBuffer", _wrap_newVertexBuffer },

		//{ "newAnimation", _wrap_newAnimation },

		{ "setColor", _wrap_setColor },
		{ "getColor", _wrap_getColor },
		{ "setBackgroundColor", _wrap_setBackgroundColor },
		{ "getBackgroundColor", _wrap_getBackgroundColor },

		{ "setFont", _wrap_setFont },

		{ "setBlendMode", _wrap_setBlendMode },
		{ "setColorMode", _wrap_setColorMode },
		{ "getBlendMode", _wrap_getBlendMode },
		{ "getColorMode", _wrap_getColorMode },
		{ "setLineWidth", _wrap_setLineWidth },
		{ "setLineStyle", _wrap_setLineStyle },
		{ "setLine", _wrap_setLine },
		{ "setLineStipple", _wrap_setLineStipple },
		{ "getLineWidth", _wrap_getLineWidth },
		{ "getLineStyle", _wrap_getLineStyle },
		{ "getLineStipple", getLineStipple },
		{ "setPointSize", _wrap_setPointSize },
		{ "setPointStyle", _wrap_setPointStyle },
		{ "setPoint", _wrap_setPoint },
		{ "getPointSize", _wrap_getPointSize },
		{ "getPointStyle", _wrap_getPointStyle },
		{ "getMaxPointSize", _wrap_getMaxPointSize },

		{ "draw", _wrap_draw },
		{ "drawTest", _wrap_drawTest },

		{ "print", _wrap_print },
		{ "printf", _wrap_printf },

		{ "setCaption", _wrap_setCaption },
		{ "getCaption", getCaption },

		{ "getWidth", _wrap_getWidth },
		{ "getHeight", _wrap_getHeight },

		{ "isCreated", _wrap_isCreated },

		{ "getModes", getModes },

		{ "setScissor", _wrap_setScissor },
		{ "getScissor", getScissor },

		{ "point", _wrap_point },
		{ "line", _wrap_line },
		{ "triangle", _wrap_triangle },
		{ "rectangle", _wrap_rectangle },
		{ "quad", _wrap_quad },
		{ "circle", _wrap_circle },

		{ "polygon", polygon },

		{ "push", _wrap_push },
		{ "pop", _wrap_pop },
		{ "rotate", _wrap_rotate },
		{ "scale", _wrap_scale },
		{ "translate", _wrap_translate },

		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "graphics", module_fn);
		luax_register_type(L, "Color", Color_mt);
		luax_register_type(L, "Font", Font_mt);
		luax_register_type(L, "Drawable", Drawable_mt);
		luax_register_type(L, "Image", Image_mt);
		//luax_register_type(L, "Animation", Animation_mt);
		luax_register_type(L, "ParticleSystem", ParticleSystem_mt);
		luax_register_type(L, "SpriteBatch", SpriteBatch_mt);
		luax_register_type(L, "VertexBuffer", VertexBuffer_mt);
		return 0;
	}

}
}

#endif // LOVE_GRAPHICS_W
