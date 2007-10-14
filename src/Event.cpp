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

	string Event::getName() const
	{
		return name;
	}

	void Event::setType(int type)
	{
		this->type = type;
	}

	void Event::setName(string name)
	{
		this->name = name;
	}


}// love
