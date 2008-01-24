/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_BALANCE_H
#define LOVE_BALANCE_H

#define LOVE_BALANCE

namespace love
{
	// BALANCEABLES (it's a word).
	enum
	{
		LOVE_IMAGE, 
		LOVE_FONT, 
		LOVE_SOUND, 
		LOVE_MUSIC, 
		LOVE_FILE, 
		LOVE_RESOURCE,
		LOVE_ANIMATION,
		LOVE_BALANCE_SIZE
	};

	struct balance_entry
	{
		int current;
		int max;
		const char * name;
	};

	// Holds actual data.
	extern balance_entry balance_data[LOVE_BALANCE_SIZE];

	/**
	* Increments the balance indicated by type.
	**/
	void balance_inc(int type);

	/**
	* Decrements the balance indicated by type.
	**/
	void balance_dec(int type);

	/**
	* Prints balance for all types.
	**/
	void balance_print();

} // love

#endif // LOVE_BALANCE_H
