/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

// File contains needed extern declarations to communicate with 
// SWIG/Lua glue.

#ifndef LOVE_LUA_GLUE_H
#define LOVE_LUA_GLUE_H

// SWIG
extern "C" {
	extern int luaopen_love(lua_State * L);
	//extern int Love_Init(lua_State * L);
}

// SWIG/lualove
extern void lualove_push_pointer(lua_State * L, void * ptr, int type, int own);

#endif // LOVE_LUA_GLUE_H
