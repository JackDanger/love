%{

#include "Graphics.h"
#include "Filesystem.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Game.h"
#include "Audio.h"
#include "Timer.h"

namespace love
{
	extern Graphics * graphics;
	extern Filesystem * filesystem;
	extern Mouse * mouse;
	extern Keyboard * keyboard;
	extern Audio * audio;
	extern Timer * timer;
	
	extern Game * game;
} // love
%}

// These are the visible devices:

namespace love
{
	extern Graphics * graphics;
	extern Mouse * mouse;
	extern Keyboard * keyboard;
	extern Audio * audio;
	extern Filesystem * filesystem;
	extern Timer * timer;
	// Also see objects.i
} // love