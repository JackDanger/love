/**
* @file lualove_globals.h
* @author Anders Ruud
* @date 2007-08-26
* @brief Contains variables then end up inside the "love" module in Lua.
**/

#ifndef LOVE_LUALOVE_GLOBALS_H 
#define LOVE_LUALOVE_GLOBALS_H 

namespace love
{
	class Keyboard;
	class Mouse;
	class AbstractDisplay;
	class Timer;
	class ObjectFactory;
	class KeyConstants;
	class AbstractGraphics;
	class AbstractSoundDevice;
	class LuaGame;
	//class LuaGame; //an extra LuaGame? if removing this kills all, then forgive me
	class GUIContainer;

	extern Keyboard * keyboard;
	extern Mouse * mouse;
	extern AbstractDisplay * display;
	extern AbstractGraphics * graphics;
	extern AbstractSoundDevice * audio;
	extern Timer * timer;
	extern ObjectFactory * objects;
	extern LuaGame * game;
	extern GUIContainer * gui;
	
} // love

#endif
