#ifndef LOVE_LUA_GLUE
#define LOVE_LUA_GLUE

// Lua
extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

extern "C" 
{
	typedef void *(*swig_converter_func)(void *);
	typedef struct swig_type_info *(*swig_dycast_func)(void **);
}

void luaPushPointer(lua_State * L, void * ptr, int type, int own);

#endif
