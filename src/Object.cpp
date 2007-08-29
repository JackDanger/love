#include "Object.h"

namespace love
{

	Object::Object() : name(""), type(LOVE_TYPE_OBJECT)
	{
	}

	Object::~Object()
	{
	}

	const std::string & Object::getName() const
	{
		return name;
	}

	std::string Object::toString() const
	{
		return "Object";
	}

	int Object::getType() const
	{
		return type;
	}

	void Object::setType(int type)
	{
		this->type = type;
	}


}// love
