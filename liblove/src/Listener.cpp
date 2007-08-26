#include "Listener.h"

namespace love
{


	Listener::Listener()
	{
	}

	Listener::~Listener()
	{
	}

	bool Listener::isActive()
	{
		return active;
	}

	void Listener::setActive(bool active)
	{
		this->active = active;
	}


}// love
