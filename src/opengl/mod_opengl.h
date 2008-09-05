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
* @date 2008-09-05
**/

#ifndef LOVE_MOD_FUSION_OPENGL_H
#define LOVE_MOD_FUSION_OPENGL_H

// Boost
#include <boost/shared_ptr.hpp>


// Function from SWIG which opens the module.
extern "C" {
    int luaopen_mod_opengl(lua_State * L);
}

// Types found:
// Sprite (SWIGTYPE_p_boost__shared_ptrT_love_opengl__Sprite_t)
// Image (SWIGTYPE_p_boost__shared_ptrT_love_opengl__Image_t)
// Animation (SWIGTYPE_p_boost__shared_ptrT_love_opengl__Animation_t)
// Color (SWIGTYPE_p_boost__shared_ptrT_love_opengl__Color_t)
// ParticleSystem (SWIGTYPE_p_boost__shared_ptrT_love_opengl__ParticleSystem_t)
// Font (SWIGTYPE_p_boost__shared_ptrT_love_opengl__Font_t)

namespace love_opengl
{

	//Forward declarations.
	class Sprite;
	class Image;
	class Animation;
	class Color;
	class ParticleSystem;
	class Font;

	bool mod_is_sprite(lua_State * L, int idx);
	boost::shared_ptr<Sprite> mod_to_sprite(lua_State * L, int idx);
	void mod_push_sprite(lua_State * L, boost::shared_ptr<Sprite> sprite);

	bool mod_is_image(lua_State * L, int idx);
	boost::shared_ptr<Image> mod_to_image(lua_State * L, int idx);
	void mod_push_image(lua_State * L, boost::shared_ptr<Image> image);

	bool mod_is_animation(lua_State * L, int idx);
	boost::shared_ptr<Animation> mod_to_animation(lua_State * L, int idx);
	void mod_push_animation(lua_State * L, boost::shared_ptr<Animation> animation);

	bool mod_is_color(lua_State * L, int idx);
	boost::shared_ptr<Color> mod_to_color(lua_State * L, int idx);
	void mod_push_color(lua_State * L, boost::shared_ptr<Color> color);

	bool mod_is_particlesystem(lua_State * L, int idx);
	boost::shared_ptr<ParticleSystem> mod_to_particlesystem(lua_State * L, int idx);
	void mod_push_particlesystem(lua_State * L, boost::shared_ptr<ParticleSystem> particlesystem);

	bool mod_is_font(lua_State * L, int idx);
	boost::shared_ptr<Font> mod_to_font(lua_State * L, int idx);
	void mod_push_font(lua_State * L, boost::shared_ptr<Font> font);

} // love_opengl

#endif
