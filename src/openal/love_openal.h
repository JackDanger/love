/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* @author Anders Ruud
* @date 2008-09-23
**/

#ifndef LOVE_MOD_OPENAL_H
#define LOVE_MOD_OPENAL_H

// LOVE
#include <love/mod.h>

// Module
#include "Sound.h"

namespace love_openal
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	pSound newSound(const char * filename);

	void play(pSound & sound);
	void pause(pSound & sound);
	void stop(pSound & sound);

	bool isPlaying(pSound & sound);
	bool isPaused(pSound & sound);
	bool isStopped(pSound & sound);

	void seek(pSound & sound);
	void rewind(pSound & sound);
}

#endif // LOVE_MOD_OPENAL_H
