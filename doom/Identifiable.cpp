#include "Identifiable.h"
#include "love_types.h"

namespace love
{

	int Identifiable::nextId = 0;

	Identifiable::Identifiable() : type(0), id(Identifiable::getNextId())
	{

	}

	Identifiable::~Identifiable()
	{
	}

	int Identifiable::getNextId()
	{
		return Identifiable::nextId++;
	}

	int Identifiable::getId() const 
	{
		return id;
	}

}