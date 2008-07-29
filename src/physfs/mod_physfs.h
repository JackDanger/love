/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This file was AUTOGENERATED by swigfusion! Please
* do not edit this file manually.
* 
* @author Anders Ruud / swigfusion
* @date 2008-07-28
**/

#ifndef LOVE_MOD_FUSION_PHYSFS_H
#define LOVE_MOD_FUSION_PHYSFS_H

// Function from SWIG which opens the module.
extern "C" {
    int luaopen_mod_physfs(lua_State * L);
}

// Types found:
// File (SWIGTYPE_p_boost__shared_ptrT_love_physfs__File_t)

namespace love_physfs
{

	bool mod_is_file(lua_State * L, int idx);
	pFile mod_to_file(lua_State * L, int idx);
	void mod_push_file(lua_State * L, pFile file);

} // love_physfs
#endif
