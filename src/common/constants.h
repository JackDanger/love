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
**/

#ifndef LOVE_CONSTANTS_H
#define LOVE_CONSTANTS_H

#include "../modules/filesystem/File.h"
#include "../modules/event/Event.h"

namespace love
{

	// Primitive types.
	// Note: unlike most of LOVE, this is modeled after the enum
	// D3DPRIMITIVETYPE in the DirectX SDK. Quads are NOT supported.
	enum
	{
		TYPE_POINTS,
		TYPE_LINES,
		TYPE_LINE_STRIP,
		TYPE_TRIANGLES,
		TYPE_TRIANGLE_STRIP,
		TYPE_TRIANGLE_FAN,
		TYPE_NUM
	};

	// Vertex Buffer directives.
	enum 
	{
		USAGE_ARRAY, 
		USAGE_DYNAMIC,
		USAGE_STATIC,
		USAGE_STREAM,
		USAGE_NUM
	};

	// Defaults.
	enum
	{
		DEFAULT_FONT, 
		DEFAULT_LOGO_128,
		DEFAULT_LOGO_256, 
		DEFAULT_MOOSE, 
		DEFAULT_VERMIN,
		DEFAULT_BIG_LOVE_BALL, 
		DEFAULT_FREECHAN, 
		DEFAULT_GREEN_BALL,
		DEFAULT_SPEAK_CLOUD
	};

	// Physics
	enum
	{
		SHAPE_CIRCLE = 1, 
		SHAPE_POLYGON,
		JOINT_DISTANCE,
		JOINT_REVOLUTE,
		JOINT_PRISMATIC,
		JOINT_MOUSE,
		JOINT_PULLEY,
		JOINT_GEAR
	};

	// Audio
	enum
	{
		AUDIO_LOOP = 0,
		AUDIO_MODE_MONO = 1,
		AUDIO_MODE_STEREO = 2,
		AUDIO_QUALITY_LOW = 11025,
		AUDIO_QUALITY_MEDIUM = 22050,
		AUDIO_QUALITY_HIGH = 44100,
		AUDIO_BUFFER_DEFAULT = 1024
	};

	// Features.
	enum
	{
		POINT_SPRITE
	};

	// Message tags.
	enum
	{
		TAG_ERROR, 
		TAG_WARNING, 
		TAG_INFO, 
		TAG_COMMAND, 
		TAG_INCOMPATIBLE
	};

	// Image optimization, etc.
	enum
	{
		IMAGE_NORMAL = 0,
		IMAGE_OPTIMIZE = 1, 
		IMAGE_PAD, 
		IMAGE_PAD_AND_OPTIMIZE
	};
		
	// Animation modes.
	enum
	{
		ANIMATION_LOOP = 1,
		ANIMATION_PLAY_ONCE,
		ANIMATION_BOUNCE
	};

	// Sprite flipping.
	enum
	{
		FLIP_NONE = 0,
		FLIP_VERTICAL, 
		FLIP_HORIZONTAL,
	};

	// Alignment.
	enum
	{
		ALIGN_LEFT, 
		ALIGN_RIGHT, 
		ALIGN_CENTER
	};

	// Blending modes
	enum
	{
		BLEND_NORMAL, 
		BLEND_ADDITIVE
	};

	// Color modes.
	enum 
	{
		COLOR_NORMAL, 
		COLOR_MODULATE
	};


	// Drawing primitives.
	enum
	{
		DRAW_LINE	= 1,
		DRAW_FILL	= 2
	};

	// Joystick values.
	enum
	{
		JOYSTICK_AXIS_HORIZONTAL = 0,
		JOYSTICK_AXIS_VERITCAL = 1,
		JOYSTICK_HAT_CENTERED = 0,
		JOYSTICK_HAT_UP = 1,
		JOYSTICK_HAT_RIGHT = 2,
		JOYSTICK_HAT_DOWN = 4,
		JOYSTICK_HAT_LEFT = 8,
		JOYSTICK_HAT_RIGHTUP = (JOYSTICK_HAT_RIGHT|JOYSTICK_HAT_UP), // 3
		JOYSTICK_HAT_RIGHTDOWN = (JOYSTICK_HAT_RIGHT|JOYSTICK_HAT_DOWN), // 6
		JOYSTICK_HAT_LEFTUP = (JOYSTICK_HAT_LEFT|JOYSTICK_HAT_UP), // 9
		JOYSTICK_HAT_LEFTDOWN = (JOYSTICK_HAT_LEFT|JOYSTICK_HAT_DOWN) // 12
	};

	// Drawing lines.
	enum
	{
		LINE_SMOOTH	= 1,
		LINE_ROUGH	= 2, 
		POINT_SMOOTH = 3, 
		POINT_ROUGH = 4,
	};

	// Mouse constants.
	enum 
	{
		MOUSE_LEFT = 1,
		MOUSE_MIDDLE = 2,
		MOUSE_RIGHT = 3,
		MOUSE_WHEELUP = 4,
		MOUSE_WHEELDOWN = 5, 
		MOUSE_NUM
	};


	// Keyboard.
	enum 
	{
		KEY_UNKNOWN		= 0,
		KEY_FIRST		= 0,
		KEY_BACKSPACE		= 8,
		KEY_TAB		= 9,
		KEY_CLEAR		= 12,
		KEY_RETURN		= 13,
		KEY_PAUSE		= 19,
		KEY_ESCAPE		= 27,
		KEY_SPACE		= 32,
		KEY_EXCLAIM		= 33,
		KEY_QUOTEDBL		= 34,
		KEY_HASH		= 35,
		KEY_DOLLAR		= 36,
		KEY_AMPERSAND		= 38,
		KEY_QUOTE		= 39,
		KEY_LEFTPAREN		= 40,
		KEY_RIGHTPAREN		= 41,
		KEY_ASTERISK		= 42,
		KEY_PLUS		= 43,
		KEY_COMMA		= 44,
		KEY_MINUS		= 45,
		KEY_PERIOD		= 46,
		KEY_SLASH		= 47,
		KEY_0			= 48,
		KEY_1			= 49,
		KEY_2			= 50,
		KEY_3			= 51,
		KEY_4			= 52,
		KEY_5			= 53,
		KEY_6			= 54,
		KEY_7			= 55,
		KEY_8			= 56,
		KEY_9			= 57,
		KEY_COLON		= 58,
		KEY_SEMICOLON		= 59,
		KEY_LESS		= 60,
		KEY_EQUALS		= 61,
		KEY_GREATER		= 62,
		KEY_QUESTION		= 63,
		KEY_AT			= 64,

		KEY_LEFTBRACKET	= 91,
		KEY_BACKSLASH		= 92,
		KEY_RIGHTBRACKET	= 93,
		KEY_CARET		= 94,
		KEY_UNDERSCORE		= 95,
		KEY_BACKQUOTE		= 96,
		KEY_a			= 97,
		KEY_b			= 98,
		KEY_c			= 99,
		KEY_d			= 100,
		KEY_e			= 101,
		KEY_f			= 102,
		KEY_g			= 103,
		KEY_h			= 104,
		KEY_i			= 105,
		KEY_j			= 106,
		KEY_k			= 107,
		KEY_l			= 108,
		KEY_m			= 109,
		KEY_n			= 110,
		KEY_o			= 111,
		KEY_p			= 112,
		KEY_q			= 113,
		KEY_r			= 114,
		KEY_s			= 115,
		KEY_t			= 116,
		KEY_u			= 117,
		KEY_v			= 118,
		KEY_w			= 119,
		KEY_x			= 120,
		KEY_y			= 121,
		KEY_z			= 122,
		KEY_DELETE		= 127,

		KEY_WORLD_0		= 160,		
		KEY_WORLD_1		= 161,
		KEY_WORLD_2		= 162,
		KEY_WORLD_3		= 163,
		KEY_WORLD_4		= 164,
		KEY_WORLD_5		= 165,
		KEY_WORLD_6		= 166,
		KEY_WORLD_7		= 167,
		KEY_WORLD_8		= 168,
		KEY_WORLD_9		= 169,
		KEY_WORLD_10		= 170,
		KEY_WORLD_11		= 171,
		KEY_WORLD_12		= 172,
		KEY_WORLD_13		= 173,
		KEY_WORLD_14		= 174,
		KEY_WORLD_15		= 175,
		KEY_WORLD_16		= 176,
		KEY_WORLD_17		= 177,
		KEY_WORLD_18		= 178,
		KEY_WORLD_19		= 179,
		KEY_WORLD_20		= 180,
		KEY_WORLD_21		= 181,
		KEY_WORLD_22		= 182,
		KEY_WORLD_23		= 183,
		KEY_WORLD_24		= 184,
		KEY_WORLD_25		= 185,
		KEY_WORLD_26		= 186,
		KEY_WORLD_27		= 187,
		KEY_WORLD_28		= 188,
		KEY_WORLD_29		= 189,
		KEY_WORLD_30		= 190,
		KEY_WORLD_31		= 191,
		KEY_WORLD_32		= 192,
		KEY_WORLD_33		= 193,
		KEY_WORLD_34		= 194,
		KEY_WORLD_35		= 195,
		KEY_WORLD_36		= 196,
		KEY_WORLD_37		= 197,
		KEY_WORLD_38		= 198,
		KEY_WORLD_39		= 199,
		KEY_WORLD_40		= 200,
		KEY_WORLD_41		= 201,
		KEY_WORLD_42		= 202,
		KEY_WORLD_43		= 203,
		KEY_WORLD_44		= 204,
		KEY_WORLD_45		= 205,
		KEY_WORLD_46		= 206,
		KEY_WORLD_47		= 207,
		KEY_WORLD_48		= 208,
		KEY_WORLD_49		= 209,
		KEY_WORLD_50		= 210,
		KEY_WORLD_51		= 211,
		KEY_WORLD_52		= 212,
		KEY_WORLD_53		= 213,
		KEY_WORLD_54		= 214,
		KEY_WORLD_55		= 215,
		KEY_WORLD_56		= 216,
		KEY_WORLD_57		= 217,
		KEY_WORLD_58		= 218,
		KEY_WORLD_59		= 219,
		KEY_WORLD_60		= 220,
		KEY_WORLD_61		= 221,
		KEY_WORLD_62		= 222,
		KEY_WORLD_63		= 223,
		KEY_WORLD_64		= 224,
		KEY_WORLD_65		= 225,
		KEY_WORLD_66		= 226,
		KEY_WORLD_67		= 227,
		KEY_WORLD_68		= 228,
		KEY_WORLD_69		= 229,
		KEY_WORLD_70		= 230,
		KEY_WORLD_71		= 231,
		KEY_WORLD_72		= 232,
		KEY_WORLD_73		= 233,
		KEY_WORLD_74		= 234,
		KEY_WORLD_75		= 235,
		KEY_WORLD_76		= 236,
		KEY_WORLD_77		= 237,
		KEY_WORLD_78		= 238,
		KEY_WORLD_79		= 239,
		KEY_WORLD_80		= 240,
		KEY_WORLD_81		= 241,
		KEY_WORLD_82		= 242,
		KEY_WORLD_83		= 243,
		KEY_WORLD_84		= 244,
		KEY_WORLD_85		= 245,
		KEY_WORLD_86		= 246,
		KEY_WORLD_87		= 247,
		KEY_WORLD_88		= 248,
		KEY_WORLD_89		= 249,
		KEY_WORLD_90		= 250,
		KEY_WORLD_91		= 251,
		KEY_WORLD_92		= 252,
		KEY_WORLD_93		= 253,
		KEY_WORLD_94		= 254,
		KEY_WORLD_95		= 255,		


		KEY_KP0		= 256,
		KEY_KP1		= 257,
		KEY_KP2		= 258,
		KEY_KP3		= 259,
		KEY_KP4		= 260,
		KEY_KP5		= 261,
		KEY_KP6		= 262,
		KEY_KP7		= 263,
		KEY_KP8		= 264,
		KEY_KP9		= 265,
		KEY_KP_PERIOD		= 266,
		KEY_KP_DIVIDE		= 267,
		KEY_KP_MULTIPLY	= 268,
		KEY_KP_MINUS		= 269,
		KEY_KP_PLUS		= 270,
		KEY_KP_ENTER		= 271,
		KEY_KP_EQUALS		= 272,


		KEY_UP			= 273,
		KEY_DOWN		= 274,
		KEY_RIGHT		= 275,
		KEY_LEFT		= 276,
		KEY_INSERT		= 277,
		KEY_HOME		= 278,
		KEY_END		= 279,
		KEY_PAGEUP		= 280,
		KEY_PAGEDOWN		= 281,


		KEY_F1			= 282,
		KEY_F2			= 283,
		KEY_F3			= 284,
		KEY_F4			= 285,
		KEY_F5			= 286,
		KEY_F6			= 287,
		KEY_F7			= 288,
		KEY_F8			= 289,
		KEY_F9			= 290,
		KEY_F10		= 291,
		KEY_F11		= 292,
		KEY_F12		= 293,
		KEY_F13		= 294,
		KEY_F14		= 295,
		KEY_F15		= 296,


		KEY_NUMLOCK		= 300,
		KEY_CAPSLOCK		= 301,
		KEY_SCROLLOCK		= 302,
		KEY_RSHIFT		= 303,
		KEY_LSHIFT		= 304,
		KEY_RCTRL		= 305,
		KEY_LCTRL		= 306,
		KEY_RALT		= 307,
		KEY_LALT		= 308,
		KEY_RMETA		= 309,
		KEY_LMETA		= 310,
		KEY_LSUPER		= 311,		/* Left "Windows" key */
		KEY_RSUPER		= 312,		/* Right "Windows" key */
		KEY_MODE		= 313,		/* "Alt Gr" key */
		KEY_COMPOSE		= 314,		/* Multi-key compose key */


		KEY_HELP		= 315,
		KEY_PRINT		= 316,
		KEY_SYSREQ		= 317,
		KEY_BREAK		= 318,
		KEY_MENU		= 319,
		KEY_POWER		= 320,		/* Power Macintosh power key */
		KEY_EURO		= 321,		/* Some european keyboards */
		KEY_UNDO		= 322,		/* Atari keyboard has Undo */

		/* Add any other keys here */

		KEY_LAST

	}; // enum


	// Type used for storing constants
	// in an array.
	typedef struct lua_constant_entry
	{
		const char * name;
		int value;
	} lua_constant_entry;

	// Constants.
	const lua_constant_entry lua_constants[] = 
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

		{ "mouse_left", MOUSE_LEFT },
		{ "mouse_middle", MOUSE_MIDDLE },
		{ "mouse_right", MOUSE_RIGHT },
		{ "mouse_wheelup", MOUSE_WHEELUP },
		{ "mouse_wheeldown", MOUSE_WHEELDOWN },

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

		{ "file_closed", filesystem::File::CLOSED },
		{ "file_read", filesystem::File::READ },
		{ "file_write", filesystem::File::WRITE },
		{ "file_append", filesystem::File::APPEND },

		{ "draw_line", 1 },
		{ "draw_fill", 2 },

		{ "line_smooth", LINE_SMOOTH },
		{ "line_rough", LINE_ROUGH },
		{ "point_smooth", POINT_SMOOTH },
		{ "point_rough", POINT_ROUGH },

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

		{ "image_normal", 0 },
		{ "image_optimize", 1 },
		{ "image_pad", 2 },
		{ "image_pad_and_optimize", 3 },

		{ "shape_circle", SHAPE_CIRCLE },
		{ "shape_polygon", SHAPE_POLYGON },
		{ "joint_distance", JOINT_DISTANCE },
		{ "joint_revolute", JOINT_REVOLUTE },
		{ "joint_prismatic", JOINT_PRISMATIC },
		{ "joint_mouse", JOINT_MOUSE },	
		{ "joint_pulley", JOINT_PULLEY },	
		{ "joint_gear", JOINT_GEAR },

		{ "joystick_axis_horizontal", JOYSTICK_AXIS_HORIZONTAL },
		{ "joystick_axis_vertical", JOYSTICK_AXIS_VERITCAL },
		{ "joystick_hat_centered", JOYSTICK_HAT_CENTERED },
		{ "joystick_hat_up", JOYSTICK_HAT_UP },
		{ "joystick_hat_right", JOYSTICK_HAT_RIGHT },
		{ "joystick_hat_down", JOYSTICK_HAT_DOWN },
		{ "joystick_hat_left", JOYSTICK_HAT_LEFT },
		{ "joystick_hat_rightup", JOYSTICK_HAT_RIGHTUP },
		{ "joystick_hat_rightdown", JOYSTICK_HAT_RIGHTDOWN },
		{ "joystick_hat_leftup", JOYSTICK_HAT_LEFTUP },
		{ "joystick_hat_leftdown", JOYSTICK_HAT_LEFTDOWN },

		{ "event_keypressed", event::Event::EVENT_KEYDOWN },
		{ "event_keyreleased", event::Event::EVENT_KEYUP },
		{ "event_mousepressed", event::Event::EVENT_MOUSEBUTTONDOWN },
		{ "event_mousereleased", event::Event::EVENT_MOUSEBUTTONUP },
		{ "event_joystickpressed", event::Event::EVENT_JOYBUTTONDOWN },
		{ "event_joystickreleased", event::Event::EVENT_JOYBUTTONUP },
		{ "event_quit", event::Event::EVENT_QUIT },

		{ "type_points", TYPE_POINTS },
		{ "type_lines", TYPE_LINES },
		{ "type_line_strip", TYPE_LINE_STRIP },
		{ "type_triangles", TYPE_TRIANGLES },
		{ "type_triangle_strip", TYPE_TRIANGLE_STRIP },
		{ "type_triangle_fan", TYPE_TRIANGLE_FAN },
		{ "type_num", TYPE_NUM },

		{ "usage_array", USAGE_ARRAY },
		{ "usage_dynamic", USAGE_DYNAMIC },
		{ "usage_static", USAGE_STATIC },
		{ "usage_stream", USAGE_STREAM },
		{ "usage_num", USAGE_NUM },

		{0, 0}, // Indicates the end

	}; // lua constants

} // love

#endif // LOVE_CONSTANTS_H
