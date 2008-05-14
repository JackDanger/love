#include "Volatile.h"

namespace love_opengl
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

}
