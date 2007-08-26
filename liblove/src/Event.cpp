#include "Event.h"

namespace love
{

	Event::Event()
	{
		setType(LOVE_TYPE_EVENT);
	}

	Event::~Event()
	{
	}

	int Event::getType() const
	{
		return type;
	}

	void Event::setType(int type)
	{
		this->type = type;
	}


}// love
