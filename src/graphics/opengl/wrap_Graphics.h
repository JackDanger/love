/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_GRAPHICS_OPENGL_WRAP_GRAPHICS_H
#define LOVE_GRAPHICS_OPENGL_WRAP_GRAPHICS_H

// LOVE
#include "wrap_Color.h"
#include "wrap_Font.h"
#include "wrap_Image.h"
#include "wrap_ParticleSystem.h"
#include "wrap_SpriteBatch.h"
#include "wrap_VertexBuffer.h"
#include "Graphics.h"

namespace love
{
namespace graphics
{
namespace opengl
{
	int _wrap_checkMode(lua_State * L);
	int _wrap_setMode(lua_State * L);
	int _wrap_toggleFullscreen(lua_State * L);
	int _wrap_reset(lua_State * L);
	int _wrap_clear(lua_State * L);
	int _wrap_present(lua_State * L);
	int _wrap_setCaption(lua_State * L);
	int _wrap_getCaption(lua_State * L);
	int _wrap_getWidth(lua_State * L);
	int _wrap_getHeight(lua_State * L);
	int _wrap_isCreated(lua_State * L);
	int _wrap_setScissor(lua_State * L);
	int _wrap_getScissor(lua_State * L);
	int _wrap_newColor(lua_State * L);
	int _wrap_newImage(lua_State * L);
	int _wrap_newFont(lua_State * L);
	int _wrap_newSpriteBatch(lua_State * L);
	int _wrap_newVertexBuffer(lua_State * L);
	int _wrap_setColor(lua_State * L);
	int _wrap_getColor(lua_State * L);
	int _wrap_setBackgroundColor(lua_State * L);
	int _wrap_getBackgroundColor(lua_State * L);
	int _wrap_setFont(lua_State * L);
	int _wrap_getFont(lua_State * L);
	int _wrap_setBlendMode(lua_State * L);
	int _wrap_setColorMode(lua_State * L);
	int _wrap_getBlendMode(lua_State * L);
	int _wrap_getColorMode(lua_State * L);
	int _wrap_setLineWidth(lua_State * L);
	int _wrap_setLineStyle(lua_State * L);
	int _wrap_setLine(lua_State * L);
	int _wrap_setLineStipple(lua_State * L);
	int _wrap_getLineWidth(lua_State * L);
	int _wrap_getLineStyle(lua_State * L);
	int _wrap_getLineStipple(lua_State * L);
	int _wrap_setPointSize(lua_State * L);
	int _wrap_setPointStyle(lua_State * L);
	int _wrap_setPoint(lua_State * L);
	int _wrap_getPointSize(lua_State * L);
	int _wrap_getPointStyle(lua_State * L);
	int _wrap_getMaxPointSize(lua_State * L);
	int _wrap_draw(lua_State * L);
	int _wrap_drawTest(lua_State * L);
	int _wrap_print(lua_State * L);
	int _wrap_printf(lua_State * L);
	int _wrap_point(lua_State * L);
	int _wrap_line(lua_State * L);
	int _wrap_triangle(lua_State * L);
	int _wrap_rectangle(lua_State * L);
	int _wrap_quad(lua_State * L);
	int _wrap_circle(lua_State * L);
	int _wrap_push(lua_State * L);
	int _wrap_pop(lua_State * L);
	int _wrap_rotate(lua_State * L);
	int _wrap_scale(lua_State * L);
	int _wrap_translate(lua_State * L);
	int wrap_Graphics_open(lua_State * L);

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_WRAP_GRAPHICS_H
