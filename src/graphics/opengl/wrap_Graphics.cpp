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
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/
#include "wrap_Graphics.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	int _wrap_checkMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_toboolean(L, 3);
		luax_pushboolean(L, Graphics::getInstance()->checkMode(w, h, fs));
		return 1;
	}

	int _wrap_setMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_optboolean(L, 3, false);
		bool vsync = luax_optboolean(L, 4, true);
		int fsaa = luaL_optint(L, 5, 0);
		luax_pushboolean(L, Graphics::getInstance()->setMode(w, h, fs, vsync, fsaa));
		return 1;
	}

	int _wrap_toggleFullscreen(lua_State * L)
	{
		luax_pushboolean(L, Graphics::getInstance()->toggleFullscreen());
		return 1;
	}

	int _wrap_reset(lua_State * L)
	{
		Graphics::getInstance()->reset();
		return 0;
	}

	int _wrap_clear(lua_State * L)
	{
		Graphics::getInstance()->clear();
		return 0;
	}

	int _wrap_present(lua_State * L)
	{
		Graphics::getInstance()->present();
		return 0;
	}

	int _wrap_setCaption(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		Graphics::getInstance()->setCaption(str);
		return 0;
	}

	int _wrap_getCaption(lua_State * L)
	{
		return Graphics::getInstance()->getCaption(L);
	}

	int _wrap_getWidth(lua_State * L)
	{
		lua_pushnumber(L, Graphics::getInstance()->getWidth());
		return 1;
	}

	int _wrap_getHeight(lua_State * L)
	{
		lua_pushnumber(L, Graphics::getInstance()->getHeight());
		return 1;
	}

	int _wrap_isCreated(lua_State * L)
	{
		luax_pushboolean(L, Graphics::getInstance()->isCreated());
		return 1;
	}

	int _wrap_getModes(lua_State * L)
	{
		return Graphics::getInstance()->getModes(L);
	}

	int _wrap_setScissor(lua_State * L)
	{
		if(lua_gettop(L) == 0)
		{
			Graphics::getInstance()->setScissor();
			return 0;
		}
	
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		int w = luaL_checkint(L, 3);
		int h = luaL_checkint(L, 4);

		Graphics::getInstance()->setScissor(x, y, w, h);
		return 0;
	}

	int _wrap_getScissor(lua_State * L)
	{
		return Graphics::getInstance()->getScissor(L);
	}

	int _wrap_newColor(lua_State * L)
	{
		int r = luaL_checkinteger(L, 1);
		int g = luaL_checkinteger(L, 2);
		int b = luaL_checkinteger(L, 3);
		int a = luaL_optint(L, 4, 255);

		Color * t = Graphics::getInstance()->newColor(r, g, b, a);

		luax_newtype(L, "Color", LOVE_GRAPHICS_COLOR_BITS, (void*)t);

		return 1;
	}

	int _wrap_newImage(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to ImageData, if necessary.
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "image", "newImageData");

		love::image::ImageData * data = luax_checktype<love::image::ImageData>(L, 1, "ImageData", LOVE_IMAGE_IMAGE_DATA_BITS);

		// Create the image.
		Image * image = Graphics::getInstance()->newImage(data);
			
		if(image == 0)
			return luaL_error(L, "Could not load image.");


		// Push the type.
		luax_newtype(L, "Image", LOVE_GRAPHICS_IMAGE_BITS, (void*)image);

		return 1;
	}

	int _wrap_newAnimation(lua_State * L)
	{
		// If string -> file
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// file -> imagedata
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "image", "newImageData");

		// imagedata -> image
		if(luax_istype(L, 1, LOVE_IMAGE_IMAGE_DATA_BITS))
			luax_convobj(L, 1, "graphics", "newImage");

		// Check the value.
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);

		Animation * animation = 0;

		if(lua_gettop(L) == 1)
		{
			animation = Graphics::getInstance()->newAnimation(image);
		}
		else 
		{
			float fw = (float)luaL_checknumber(L, 2);
			float fh = (float)luaL_checknumber(L, 3);
			float delay = (float)luaL_checknumber(L, 4);
			int num = luaL_optint(L, 5, 0);
			animation = Graphics::getInstance()->newAnimation(image, fw, fh, delay, num);
		}

		if(animation == 0)
			return luaL_error(L, "Could not load the Animation");
		
		luax_newtype(L, "Animation", LOVE_GRAPHICS_ANIMATION_BITS, (void*)animation);
		return 1;
	}

	int _wrap_newFont(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Check the value.
		love::filesystem::File * file = luax_checktype<love::filesystem::File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);

		// Second optional parameter can be a number:
		int size = luaL_optint(L, 2, 12);

		Font * font = Graphics::getInstance()->newFont(file, size);

		if(font == 0)
			return luaL_error(L, "Could not load the font");
		
		luax_newtype(L, "Font", LOVE_GRAPHICS_FONT_BITS, (void*)font);
		
		return 1;
	}

	int _wrap_newImageFont(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		// Convert to Image, if necessary.
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
			luax_convobj(L, 1, "graphics", "newImage");

		// Check the value.
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);

		const char * glyphs = luaL_checkstring(L, 2);

		Font * font = Graphics::getInstance()->newImageFont(image, glyphs);

		if(font == 0)
			return luaL_error(L, "Could not load the font");

		luax_newtype(L, "Font", LOVE_GRAPHICS_FONT_BITS, (void*)font);
		
		return 1;
	}

	int _wrap_newSpriteBatch(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);
		int size = luaL_optint(L, 2, 1000);
		int usage = luaL_optint(L, 3, USAGE_ARRAY);
		SpriteBatch * t = Graphics::getInstance()->newSpriteBatch(image, size, usage);
		luax_newtype(L, "SpriteBatch", LOVE_GRAPHICS_SPRITE_BATCH_BITS, (void*)t);
		return 1;
	}

	int _wrap_newVertexBuffer(lua_State * L)
	{

		Image * image;
		int type, usage, size;

		if(luax_istype(L, 1, LOVE_GRAPHICS_IMAGE_BITS))
		{
			image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);
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

		VertexBuffer * t = Graphics::getInstance()->newVertexBuffer(image, size, type, usage);
		luax_newtype(L, "VertexBuffer", LOVE_GRAPHICS_VERTEX_BUFFER_BITS, (void*)t);
		return 1;
	}

	int _wrap_setColor(lua_State * L)
	{
		if(luax_istype(L, 1, LOVE_GRAPHICS_COLOR_BITS))
		{
			Color * color = luax_checktype<Color>(L, 1, "Color", LOVE_GRAPHICS_COLOR_BITS);
			Graphics::getInstance()->setColor(color);
			return 0;
		}

		int r = luaL_checkint(L, 1);
		int g = luaL_checkint(L, 2);
		int b = luaL_checkint(L, 3);
		int a = luaL_optint(L, 4, 255);

		Graphics::getInstance()->setColor(r, g, b, a);

		return 1;
	}

	int _wrap_getColor(lua_State * L)
	{
		Color * color = Graphics::getInstance()->getColor();
		luax_newtype(L, "Color", LOVE_GRAPHICS_COLOR_BITS, (void*)color);
		return 1;
	}

	int _wrap_setBackgroundColor(lua_State * L)
	{
		if(luax_istype(L, 1, LOVE_GRAPHICS_COLOR_BITS))
		{
			Color * color = luax_checktype<Color>(L, 1, "Color", LOVE_GRAPHICS_COLOR_BITS);
			Graphics::getInstance()->setBackgroundColor(color);
			return 0;
		}

		int r = luaL_checkint(L, 1);
		int g = luaL_checkint(L, 1);
		int b = luaL_checkint(L, 1);

		Graphics::getInstance()->setBackgroundColor(r, g, b);

		return 1;
	}

	int _wrap_getBackgroundColor(lua_State * L)
	{
		Color * color = Graphics::getInstance()->getBackgroundColor();
		luax_newtype(L, "Color", LOVE_GRAPHICS_COLOR_BITS, (void*)color);
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
		if(luax_istype(L, 1, LOVE_FILESYSTEM_FILE_BITS))
		{
			love::filesystem::File * file = luax_checktype<love::filesystem::File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);
			Graphics::getInstance()->setFont(file, size);
			return 0;
		}

		Font * font = luax_checktype<Font>(L, 1, "Font", LOVE_GRAPHICS_FONT_BITS);
		Graphics::getInstance()->setFont(font);
		return 0;
	}

	int _wrap_getFont(lua_State * L)
	{
		Font * f = Graphics::getInstance()->getFont();

		if(f == 0)
			return 0;

		f->retain();
		luax_newtype(L, "Font", LOVE_GRAPHICS_FONT_BITS, (void*)f);
		return 1;
	}

	int _wrap_setBlendMode(lua_State * L)
	{
		int mode = luaL_checkint(L, 1);
		Graphics::getInstance()->setBlendMode(mode);
		return 0;
	}

	int _wrap_setColorMode(lua_State * L)
	{
		int mode = luaL_checkint(L, 1);
		Graphics::getInstance()->setColorMode(mode);
		return 0;
	}

	int _wrap_getBlendMode(lua_State * L)
	{
		lua_pushinteger(L, Graphics::getInstance()->getBlendMode());
		return 1;
	}

	int _wrap_getColorMode(lua_State * L)
	{
		lua_pushinteger(L, Graphics::getInstance()->getColorMode());
		return 1;
	}

	int _wrap_setLineWidth(lua_State * L)
	{
		float width = (float)luaL_checknumber(L, 1);
		Graphics::getInstance()->setLineWidth(width);
		return 0;
	}

	int _wrap_setLineStyle(lua_State * L)
	{
		int style = luaL_checkint(L, 1);
		Graphics::getInstance()->setLineStyle(style);
		return 0;
	}

	int _wrap_setLine(lua_State * L)
	{
		float width = (float)luaL_checknumber(L, 1);
		int style = luaL_optint(L, 2, LINE_SMOOTH);
		Graphics::getInstance()->setLine(width, style);
		return 0;
	}

	int _wrap_setLineStipple(lua_State * L)
	{
		if(lua_gettop(L) == 0)
		{
			Graphics::getInstance()->setLineStipple();
			return 0;
		}

		unsigned short pattern = (unsigned short)luaL_checkint(L, 1);
		int repeat = luaL_optint(L, 2, 1);
		Graphics::getInstance()->setLineStipple(pattern, repeat);
		return 0;
	}

	int _wrap_getLineWidth(lua_State * L)
	{
		lua_pushnumber(L, Graphics::getInstance()->getLineWidth());
		return 1;
	}

	int _wrap_getLineStyle(lua_State * L)
	{
		lua_pushinteger(L, Graphics::getInstance()->getLineStyle());
		return 1;
	}

	int _wrap_getLineStipple(lua_State * L)
	{
		return Graphics::getInstance()->getLineStipple(L);
	}

	int _wrap_setPointSize(lua_State * L)
	{
		float size = (float)luaL_checknumber(L, 1);
		Graphics::getInstance()->setPointSize(size);
		return 0;
	}

	int _wrap_setPointStyle(lua_State * L)
	{
		int style = luaL_checkint(L, 1);
		Graphics::getInstance()->setPointStyle(style);
		return 0;
	}

	int _wrap_setPoint(lua_State * L)
	{
		float size = (float)luaL_checknumber(L, 1);
		int style = luaL_optint(L, 2, POINT_SMOOTH);
		Graphics::getInstance()->setPoint(size, style);
		return 0;
	}

	int _wrap_getPointSize(lua_State * L)
	{
		lua_pushnumber(L, Graphics::getInstance()->getPointSize());
		return 1;
	}

	int _wrap_getPointStyle(lua_State * L)
	{
		lua_pushinteger(L, Graphics::getInstance()->getPointStyle());
		return 1;
	}

	int _wrap_getMaxPointSize(lua_State * L)
	{
		lua_pushnumber(L, Graphics::getInstance()->getMaxPointSize());
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
		Drawable * drawable = luax_checktype<Drawable>(L, 1, "Drawable", LOVE_GRAPHICS_DRAWABLE_BITS);
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
	* @param rx The upper-left corner of the source rectangle along the x-axis.
	* @param ry The upper-left corner of the source rectangle along the y-axis.
	* @param rw The width of the source rectangle.
	* @param rw The height of the source rectangle.
	**/
	int _wrap_draws(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		float rx = (float)luaL_optnumber(L, 9, 0);
		float ry = (float)luaL_optnumber(L, 10, 0);
		float rw = (float)luaL_optnumber(L, 11, image->getWidth());
		float rh = (float)luaL_optnumber(L, 12, image->getHeight());
		image->draws(x, y, angle, sx, sy, ox, oy, rx, ry, rw, rh);
		return 0;
	}

	int _wrap_drawTest(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", LOVE_GRAPHICS_IMAGE_BITS);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		Graphics::getInstance()->drawTest(image, x, y, angle, sx, sy, ox, oy);
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
			Graphics::getInstance()->print(str, x, y);
			break;
		case 4:
			Graphics::getInstance()->print(str, x, y, angle);
			break;
		case 5:
			Graphics::getInstance()->print(str, x, y, angle, sx);
			break;
		case 6:
			Graphics::getInstance()->print(str, x, y, angle, sx, sy);
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
		Graphics::getInstance()->printf(str, x, y, wrap, align);
		return 0;
	}

	int _wrap_point(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		Graphics::getInstance()->point(x, y);
		return 0;
	}

	int _wrap_line(lua_State * L)
	{
		float x1 = (float)luaL_checknumber(L, 1);
		float y1 = (float)luaL_checknumber(L, 2);
		float x2 = (float)luaL_checknumber(L, 3);
		float y2 = (float)luaL_checknumber(L, 4);
		Graphics::getInstance()->line(x1, y1, x2, y2);
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
		Graphics::getInstance()->triangle(type, x1, y1, x2, y2, x3, y3);
		return 0;
	}

	int _wrap_rectangle(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float w = (float)luaL_checknumber(L, 4);
		float h = (float)luaL_checknumber(L, 5);
		Graphics::getInstance()->rectangle(type, x, y, w, h);
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
		Graphics::getInstance()->quad(type, x1, y1, x2, y2, x3, y3, x4, y4);
		return 0;
	}

	int _wrap_circle(lua_State * L)
	{
		int type = luaL_checkint(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float radius = (float)luaL_checknumber(L, 4);
		int points = luaL_optint(L, 5, 10);
		Graphics::getInstance()->circle(type, x, y, radius, points);
		return 0;
	}

	int _wrap_polygon(lua_State * L)
	{
		return Graphics::getInstance()->polygon(L);
	}

	int _wrap_push(lua_State * L)
	{
		Graphics::getInstance()->push();
		return 0;
	}

	int _wrap_pop(lua_State * L)
	{
		Graphics::getInstance()->pop();
		return 0;
	}

	int _wrap_rotate(lua_State * L)
	{
		float deg = (float)luaL_checknumber(L, 1);
		Graphics::getInstance()->rotate(deg);
		return 0;
	}

	int _wrap_scale(lua_State * L)
	{
		float sx = (float)luaL_optnumber(L, 1, 1.0f);
		float sy = (float)luaL_optnumber(L, 2, sx);
		Graphics::getInstance()->scale(sx, sy);
		return 0;
	}

	int _wrap_translate(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		Graphics::getInstance()->translate(x, y);
		return 0;
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Graphics_functions[] = {
		{ "checkMode", _wrap_checkMode },
		{ "setMode", _wrap_setMode },
		{ "toggleFullscreen", _wrap_toggleFullscreen },
		{ "reset", _wrap_reset },
		{ "clear", _wrap_clear },
		{ "present", _wrap_present },

		{ "newColor", _wrap_newColor },
		{ "newImage", _wrap_newImage },
		{ "newAnimation", _wrap_newAnimation },
		{ "newFont", _wrap_newFont },
		{ "newImageFont", _wrap_newImageFont },
		{ "newSpriteBatch", _wrap_newSpriteBatch },
		{ "newVertexBuffer", _wrap_newVertexBuffer },

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
		{ "getLineStipple", _wrap_getLineStipple },
		{ "setPointSize", _wrap_setPointSize },
		{ "setPointStyle", _wrap_setPointStyle },
		{ "setPoint", _wrap_setPoint },
		{ "getPointSize", _wrap_getPointSize },
		{ "getPointStyle", _wrap_getPointStyle },
		{ "getMaxPointSize", _wrap_getMaxPointSize },

		{ "draw", _wrap_draw },
		{ "draws", _wrap_draws },
		{ "drawTest", _wrap_drawTest },

		{ "print", _wrap_print },
		{ "printf", _wrap_printf },

		{ "setCaption", _wrap_setCaption },
		{ "getCaption", _wrap_getCaption },

		{ "getWidth", _wrap_getWidth },
		{ "getHeight", _wrap_getHeight },

		{ "isCreated", _wrap_isCreated },

		{ "getModes", _wrap_getModes },

		{ "setScissor", _wrap_setScissor },
		{ "getScissor", _wrap_getScissor },

		{ "point", _wrap_point },
		{ "line", _wrap_line },
		{ "triangle", _wrap_triangle },
		{ "rectangle", _wrap_rectangle },
		{ "quad", _wrap_quad },
		{ "circle", _wrap_circle },

		{ "polygon", _wrap_polygon },

		{ "push", _wrap_push },
		{ "pop", _wrap_pop },
		{ "rotate", _wrap_rotate },
		{ "scale", _wrap_scale },
		{ "translate", _wrap_translate },

		{ 0, 0 }
	};

	// Types for this module.
	const lua_CFunction wrap_Graphics_types[] = {
		wrap_Color_open, 
		wrap_Font_open, 
		wrap_Image_open, 
		wrap_Animation_open, 
		wrap_ParticleSystem_open, 
		wrap_SpriteBatch_open, 
		wrap_VertexBuffer_open, 
		0		
	};

	int wrap_Graphics_open(lua_State * L)
	{
		return luax_register_module(L, Graphics::getInstance(), wrap_Graphics_functions, wrap_Graphics_types);
	}

} // opengl
} // graphics
} // love
