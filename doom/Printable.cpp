#include "Printable.h"

namespace love
{

	Printable::Printable()
	{
	}

	Printable::Printable(std::string str)
	{
		this->str = str;
	}

	Printable::~Printable()
	{
	}

	string Printable::toString()
	{
		return str;
	}
}// love