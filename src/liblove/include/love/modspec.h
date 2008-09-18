/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* This file contains struct types for the standard
* modules. Some modules require internal communication, 
* and the available functions at any time are defined here.
* 
*/

#ifndef LOVE_MODSPEC_H
#define LOVE_MODSPEC_H

// LOVE
#include "Game.h"
#include "File.h"

namespace love
{
	class Core;

	/**
	* A modspec (name created in lack of a better term)
	* is the "specification" of a standard module. In 
	* other terms, it's a collection of function 
	* pointers that will be available to all other modules.
	**/
	struct modspec
	{
		bool loaded;

		modspec();

		/**
		* This function verifies that all required
		* function pointers has been set, and returns
		* false if that is not the case. (True otherwise).
		**/
		virtual bool verify() = 0;
	};

	struct Filesystem : public modspec
	{

		Filesystem();

		// Function pointers.
		pFile * (*getFile)(const char *, int);
		bool (*exists)(const std::string &);
		bool (*setSaveDirectory)(const std::string &);
		bool (*addDirectory)(const std::string &);
		const char * (*getBaseDirectory)();

		// From module.
		bool verify();
	};

	struct Graphics : public modspec
	{
		Graphics();

		// Function pointers.
		void (*clear)();
		void (*present)();
		void (*reset)();
		bool (*setMode)(int, int, bool, bool, int);
		bool (*isCreated)();
		void (*setCaption)(const char *);

		// From module.
		bool verify();
	};

	struct Timer: public modspec
	{
		Timer();

		// Function pointers.
		void (*step)();
		float (*getDelta)();

		// From module.
		bool verify();
	};

	struct System : public modspec
	{
		System();

		// Function pointers.
		const pGame & (*getGame)();
		void (*error)(const char *);

		// From module.
		bool verify();
	};

	/**
	* Modules with no required function
	* pointers follow.
	**/

	struct Audio : public modspec 
	{
		// From module.
		bool verify();
	};

	struct Mouse : public modspec 
	{
		// From module.
		bool verify();
	};

	struct Keyboard : public modspec 
	{
		// From module.
		bool verify();
	};

	struct Joystick : public modspec 
	{
		// From module.
		bool verify();
	};
}

#endif // LOVE_MODSPEC_H
