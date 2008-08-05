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
* @date 2008-08-05
**/

#ifndef LOVE_MOD_FUSION_SDLMIXER_H
#define LOVE_MOD_FUSION_SDLMIXER_H

#include <boost/shared_ptr.hpp>

// Function from SWIG which opens the module.
extern "C" {
    int luaopen_mod_sdlmixer(lua_State * L);
}

// Types found:
// Sound (SWIGTYPE_p_boost__shared_ptrT_love_sdlmixer__Sound_t)
// Music (SWIGTYPE_p_boost__shared_ptrT_love_sdlmixer__Music_t)

namespace love_sdlmixer
{

	//Forward declarations.
	class Sound;
	class Music;

	bool mod_is_sound(lua_State * L, int idx);
	boost::shared_ptr<Sound> mod_to_sound(lua_State * L, int idx);
	void mod_push_sound(lua_State * L, boost::shared_ptr<Sound> sound);

	bool mod_is_music(lua_State * L, int idx);
	boost::shared_ptr<Music> mod_to_music(lua_State * L, int idx);
	void mod_push_music(lua_State * L, boost::shared_ptr<Music> music);

} // love_sdlmixer
#endif
