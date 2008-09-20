/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-04-04
*/

#ifndef LOVE_MOD_SYSTEM_CONSTANTS_H
#define LOVE_MOD_SYSTEM_CONSTANTS_H

// LOVE
#include <love/constants.h>

namespace love_system
{

	// Type used for storing constants
	// in an array.
	typedef struct constant_entry
	{
		const char * name;
		int value;
	} constant_entry;

	// Constants.
	static const constant_entry constants[] = 
	{
		{ "key_unknown", 0 },
		{ "key_first", 0 },
		{ "key_backspace", 8 },
		{ "key_tab", 9 },
		{ "key_clear", 12 },
		{ "key_return", 13 },
		{ "key_pause", 19 },
		{ "key_escape", 27 },
		{ "key_space", 32 },
		{ "key_exclaim", 33 },
		{ "key_quotedbl", 34 },
		{ "key_hash", 35 },
		{ "key_dollar", 36 },
		{ "key_ampersand", 38 },
		{ "key_quote", 39 },
		{ "key_leftparen", 40 },
		{ "key_rightparen", 41 },
		{ "key_asterisk", 42 },
		{ "key_plus", 43 },
		{ "key_comma", 44 },
		{ "key_minus", 45 },
		{ "key_period", 46 },
		{ "key_slash", 47 },

		{ "key_0", 48 },
		{ "key_1", 49 },
		{ "key_2", 50 },
		{ "key_3", 51 },
		{ "key_4", 52 },
		{ "key_5", 53 },
		{ "key_6", 54 },
		{ "key_7", 55 },
		{ "key_8", 56 },
		{ "key_9", 57 },

		{ "key_colon", 58 },
		{ "key_semicolon", 59 },
		{ "key_less", 60 },
		{ "key_equals", 61 },
		{ "key_greater", 62 },
		{ "key_question", 63 },
		{ "key_at", 64 },

		{ "key_leftbracket", 91 },
		{ "key_backslash", 92 },
		{ "key_rightbracket", 93 },
		{ "key_caret", 94 },
		{ "key_underscore", 95 },
		{ "key_backquote", 96 },

		{ "key_a", 97 },
		{ "key_b", 98 },
		{ "key_c", 99 },
		{ "key_d", 100 },
		{ "key_e", 101 },
		{ "key_f", 102 },
		{ "key_g", 103 },
		{ "key_h", 104 },
		{ "key_i", 105 },
		{ "key_j", 106 },
		{ "key_k", 107 },
		{ "key_l", 108 },
		{ "key_m", 109 },
		{ "key_n", 110 },
		{ "key_o", 111 },
		{ "key_p", 112 },
		{ "key_q", 113 },
		{ "key_r", 114 },
		{ "key_s", 115 },
		{ "key_t", 116 },
		{ "key_u", 117 },
		{ "key_v", 118 },
		{ "key_w", 119 },
		{ "key_x", 120 },
		{ "key_y", 121 },
		{ "key_z", 122 },
		{ "key_delete", 127 },

		{ "key_kp0", 256 },
		{ "key_kp1", 257 },
		{ "key_kp2", 258 },
		{ "key_kp3", 259 },
		{ "key_kp4", 260 },
		{ "key_kp5", 261 },
		{ "key_kp6", 262 },
		{ "key_kp7", 263 },
		{ "key_kp8", 264 },
		{ "key_kp9", 265 },
		{ "key_kp_period", 266 },
		{ "key_kp_divide", 267 },
		{ "key_kp_multiply", 268 },
		{ "key_kp_minus", 269 },
		{ "key_kp_plus", 270 },
		{ "key_kp_enter", 271 },
		{ "key_kp_equals", 272 },

		{ "key_up", 273 },
		{ "key_down", 274 },
		{ "key_right", 275 },
		{ "key_left", 276 },
		{ "key_insert", 277 },
		{ "key_home", 278 },
		{ "key_end", 279 },
		{ "key_pageup", 280 },
		{ "key_pagedown", 281 },

		{ "key_f1", 282 },
		{ "key_f2", 283 },
		{ "key_f3", 284 },
		{ "key_f4", 285 },
		{ "key_f5", 286 },
		{ "key_f6", 287 },
		{ "key_f7", 288 },
		{ "key_f8", 289 },
		{ "key_f9", 290 },
		{ "key_f10", 291 },
		{ "key_f11", 292 },
		{ "key_f12", 293 },
		{ "key_f13", 294 },
		{ "key_f14", 295 },
		{ "key_f15", 296 },

		{ "key_numlock", 300 },
		{ "key_capslock", 301 },
		{ "key_scrollock", 302 },
		{ "key_rshift", 303 },
		{ "key_lshift", 304 },
		{ "key_rctrl", 305 },
		{ "key_lctrl", 306 },
		{ "key_ralt", 307 },
		{ "key_lalt", 308 },
		{ "key_rmeta", 309 },
		{ "key_lmeta", 310 },
		{ "key_lsuper", 311 },
		{ "key_rsuper", 312 },
		{ "key_mode", 313 },
		{ "key_compose", 314 },

		{ "key_help", 315 },
		{ "key_print", 316 },
		{ "key_sysreq", 317 },
		{ "key_break", 318 },
		{ "key_menu", 319 },
		{ "key_power", 320 },
		{ "key_euro", 321 },
		{ "key_undo", 322 },

		{ "mouse_left", love::MOUSE_LEFT },
		{ "mouse_middle", love::MOUSE_MIDDLE },
		{ "mouse_right", love::MOUSE_RIGHT },
		{ "mouse_wheelup", love::MOUSE_WHEELUP },
		{ "mouse_wheeldown", love::MOUSE_WHEELDOWN },

		{ "align_left", 0 },
		{ "align_right", 1 },
		{ "align_center", 2 },

		{ "mode_loop", 1 },
		{ "mode_once", 2 },
		{ "mode_bounce", 3 },

		{ "blend_normal", 0 },
		{ "blend_additive", 1 },
		{ "color_normal", 0 },
		{ "color_modulate", 1 },

		{ "file_write", 0 },
		{ "file_read", 1 },
		{ "file_append", 2 },
		{ "dir_game", 3 },
		{ "dir_save", 4 },

		{ "draw_line", 1 },
		{ "draw_fill", 2 },

		{ "line_smooth", love::LINE_SMOOTH },
		{ "line_rough", love::LINE_ROUGH },
		{ "point_smooth", love::POINT_SMOOTH },
		{ "point_rough", love::POINT_ROUGH },

		{ "tag_error", 0 },
		{ "tag_warning", 1 },
		{ "tag_info", 2 },
		{ "tag_command", 3 },
		{ "tag_incompatible", 4 },

		{ "default_font", 0 },
		{ "default_logo_128", 1 },
		{ "default_logo_256", 2 },
		{ "default_moose", 3 },
		{ "default_vermin", 4 },
		{ "default_big_love_ball", 5 },
		{ "default_freechan", 6 },
		{ "default_green_ball", 7 },
		{ "default_speak_cloud", 8 },

		{ "point_sprite", 0 },

		{ "audio_loop", 0 },
		{ "audio_mode_mono", 1 },
		{ "audio_mode_stereo", 2 },
		{ "audio_quality_low", 11025 },
		{ "audio_quality_medium", 22050 },
		{ "audio_quality_high", 44100 },
		{ "audio_buffer_default", 1024 },

		{ "image_optimize", 1 },
		{ "image_pad", 2 },
		{ "image_pad_and_optimize", 3 },

		{ "shape_circle", love::SHAPE_CIRCLE },
		{ "shape_polygon", love::SHAPE_POLYGON },
		{ "joint_distance", love::JOINT_DISTANCE },
		{ "joint_revolute", love::JOINT_REVOLUTE },
		{ "joint_prismatic", love::JOINT_PRISMATIC },
		{ "joint_mouse", love::JOINT_MOUSE },	
		{ "joint_pulley", love::JOINT_PULLEY },	
		{ "joint_gear", love::JOINT_GEAR },

		{ "joystick_axis_horizontal", love::JOYSTICK_AXIS_HORIZONTAL },
		{ "joystick_axis_vertical", love::JOYSTICK_AXIS_VERITCAL },
		{ "joystick_hat_centered", love::JOYSTICK_HAT_CENTERED },
		{ "joystick_hat_up", love::JOYSTICK_HAT_UP },
		{ "joystick_hat_right", love::JOYSTICK_HAT_RIGHT },
		{ "joystick_hat_down", love::JOYSTICK_HAT_DOWN },
		{ "joystick_hat_left", love::JOYSTICK_HAT_LEFT },
		{ "joystick_hat_rightup", love::JOYSTICK_HAT_RIGHTUP },
		{ "joystick_hat_rightdown", love::JOYSTICK_HAT_RIGHTDOWN },
		{ "joystick_hat_leftup", love::JOYSTICK_HAT_LEFTUP },
		{ "joystick_hat_leftdown", love::JOYSTICK_HAT_LEFTDOWN },

		{0, 0}, // Indicates the end
	};

} // love_system

#endif
