#include "Initializable.h"

namespace love
{

	Initializable::Initializable() : inited(false)
	{
	}
	
	Initializable::~Initializable()
	{
	
	}
	
	bool Initializable::isInited() const
	{
		return inited;
	}
}
