/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_H
#define LOVE_H

#define LOVE_DEBUG _DEBUG
#define LOVE_VERBOSE LOVE_DEBUG

namespace love
{

	/**
	* Forward declarations.
	**/

	class Game;
	class Display;
	class Graphics;
	class Timer;
	class Filesystem;
	class Audio;
	class Mouse;
	class Keyboard;

	/**
	* Globals.
	**/

	// The current game. Declared in love.cpp.
	extern Game * game;

	// Global devices. The variables themselves are declared in love.cpp, 
	// but the actual devices are created in the appropriate platform code.
	extern Display * display;
	extern Graphics * graphics;
	extern Audio * audio;
	extern Timer * timer;
	extern Filesystem * filesystem;
	extern Mouse * mouse;
	extern Keyboard * keyboard;

	/**
	* Functions.
	**/

	/**
	* Inits LÖVE with command line parameters. Returns
	* true if no problem, false otherwise.
	**/
	bool init(int argc, char* argv[]);

	/**
	* Frees whatever init allocates.
	**/
	void free();

	/**
	* Causes LOVE to quit.
	**/
	void quit();

	/** 
	* Issue an error using printf format.
	**/
	void error(const char * text, ...);

	/// Event handlers.
	void update(float dt);
	void render();
	void key_pressed(int key);
	void key_released(int key);
	void mouse_pressed(float x, float y, int button);
	void mouse_released(float x, float y, int button);

} // love

#endif // LOVE_H
