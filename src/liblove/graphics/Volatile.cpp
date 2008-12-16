/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
**/

#include "Volatile.h"

namespace love
{

	// Static members.
	std::list<Volatile *> Volatile::all;

	Volatile::Volatile()
	{
		// Insert this object into "all".
		all.push_back(this);
	}

	Volatile::~Volatile()
	{
		// Remove the pointer to this object.
		all.remove(this);		
	}

	bool Volatile::loadAll()
	{
		bool success = true;
		std::list<Volatile *>::iterator i = all.begin();

		while( i != all.end() )
		{
			success = success && (*i)->loadVolatile();
			i++;
		}

		return success;
	}

	void Volatile::unloadAll()
	{
		std::list<Volatile *>::iterator i = all.begin();

		while( i != all.end() )
		{
			(*i)->unloadVolatile();
			i++;
		}
	}

} // love
