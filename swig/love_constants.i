
%{

#include "love_mouse.h"

%}

/**
* Keyboard constants.
**/
%constant const int key_unknown = 0;
%constant const int key_first = 0;
%constant const int key_backspace = 8;
%constant const int key_tab = 9;
%constant const int key_clear = 12;
%constant const int key_return = 13;
%constant const int key_pause = 19;
%constant const int key_escape = 27;
%constant const int key_space = 32;
%constant const int key_exclaim = 33;
%constant const int key_quotedbl = 34;
%constant const int key_hash = 35;
%constant const int key_dollar = 36;
%constant const int key_ampersand = 38;
%constant const int key_quote = 39;
%constant const int key_leftparen = 40;
%constant const int key_rightparen = 41;
%constant const int key_asterisk = 42;
%constant const int key_plus = 43;
%constant const int key_comma = 44;
%constant const int key_minus = 45;
%constant const int key_period = 46;
%constant const int key_slash = 47;
%constant const int key_0 = 48;
%constant const int key_1 = 49;
%constant const int key_2 = 50;
%constant const int key_3 = 51;
%constant const int key_4 = 52;
%constant const int key_5 = 53;
%constant const int key_6 = 54;
%constant const int key_7 = 55;
%constant const int key_8 = 56;
%constant const int key_9 = 57;
%constant const int key_colon = 58;
%constant const int key_semicolon = 59;
%constant const int key_less = 60;
%constant const int key_equals = 61;
%constant const int key_greater = 62;
%constant const int key_question = 63;
%constant const int key_at = 64;

%constant const int key_leftbracket = 91;
%constant const int key_backslash = 92;
%constant const int key_rightbracket = 93;
%constant const int key_caret = 94;
%constant const int key_underscore = 95;
%constant const int key_backquote = 96;
%constant const int key_a = 97;
%constant const int key_b = 98;
%constant const int key_c = 99;
%constant const int key_d = 100;
%constant const int key_e = 101;
%constant const int key_f = 102;
%constant const int key_g = 103;
%constant const int key_h = 104;
%constant const int key_i = 105;
%constant const int key_j = 106;
%constant const int key_k = 107;
%constant const int key_l = 108;
%constant const int key_m = 109;
%constant const int key_n = 110;
%constant const int key_o = 111;
%constant const int key_p = 112;
%constant const int key_q = 113;
%constant const int key_r = 114;
%constant const int key_s = 115;
%constant const int key_t = 116;
%constant const int key_u = 117;
%constant const int key_v = 118;
%constant const int key_w = 119;
%constant const int key_x = 120;
%constant const int key_y = 121;
%constant const int key_z = 122;
%constant const int key_delete = 127;

%constant const int key_kp0 = 256;
%constant const int key_kp1 = 257;
%constant const int key_kp2 = 258;
%constant const int key_kp3 = 259;
%constant const int key_kp4 = 260;
%constant const int key_kp5 = 261;
%constant const int key_kp6 = 262;
%constant const int key_kp7 = 263;
%constant const int key_kp8 = 264;
%constant const int key_kp9 = 265;
%constant const int key_kp_period = 266;
%constant const int key_kp_divide = 267;
%constant const int key_kp_multiply = 268;
%constant const int key_kp_minus = 269;
%constant const int key_kp_plus = 270;
%constant const int key_kp_enter = 271;
%constant const int key_kp_equals = 272;

%constant const int key_up = 273;
%constant const int key_down = 274;
%constant const int key_right = 275;
%constant const int key_left = 276;
%constant const int key_insert = 277;
%constant const int key_home = 278;
%constant const int key_end = 279;
%constant const int key_pageup = 280;
%constant const int key_pagedown = 281;

%constant const int key_f1 = 282;
%constant const int key_f2 = 283;
%constant const int key_f3 = 284;
%constant const int key_f4 = 285;
%constant const int key_f5 = 286;
%constant const int key_f6 = 287;
%constant const int key_f7 = 288;
%constant const int key_f8 = 289;
%constant const int key_f9 = 290;
%constant const int key_f10 = 291;
%constant const int key_f11 = 292;
%constant const int key_f12 = 293;
%constant const int key_f13 = 294;
%constant const int key_f14 = 295;
%constant const int key_f15 = 296;

%constant const int key_numlock = 300;
%constant const int key_capslock = 301;
%constant const int key_scrollock = 302;
%constant const int key_rshift = 303;
%constant const int key_lshift = 304;
%constant const int key_rctrl = 305;
%constant const int key_lctrl = 306;
%constant const int key_ralt = 307;
%constant const int key_lalt = 308;
%constant const int key_rmeta = 309;
%constant const int key_lmeta = 310;
%constant const int key_lsuper = 311;
%constant const int key_rsuper = 312;
%constant const int key_mode = 313;
%constant const int key_compose = 314;

%constant const int key_help = 315;
%constant const int key_print = 316;
%constant const int key_sysreq = 317;
%constant const int key_break = 318;
%constant const int key_menu = 319;
%constant const int key_power = 320;
%constant const int key_euro = 321;
%constant const int key_undo = 322;

/**
* Mouse button constants.
**/
%constant const int mouse_left  = love::LOVE_MOUSE_LEFT;
%constant const int mouse_middle  = love::LOVE_MOUSE_MIDDLE;
%constant const int mouse_right  = love::LOVE_MOUSE_RIGHT;
%constant const int mouse_wheelup  = love::LOVE_MOUSE_WHEELUP;
%constant const int mouse_wheeldown  = love::LOVE_MOUSE_WHEELDOWN;

/**
* Text constants.
**/
%constant const int align_left = 1;
%constant const int align_right = 2;
%constant const int align_center = 3;
%constant const int align_top = 4;
%constant const int align_bottom = 5;

/**
* Menu types.
**/
%constant const int menu_vertical = 1;
%constant const int menu_horizontal = 2;
/**
* Slider types.
**/
%constant const int slider_horizontal = 0;
%constant const int slider_vertical = 1;

/**
* Animated color modes.
**/
%constant const int mode_loop = 1;
%constant const int mode_once = 2;
%constant const int mode_bounce = 3;

/**
* Event types.
**/