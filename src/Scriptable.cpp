#include "Scriptable.h"

namespace love
{

	Scriptable::Scriptable()
	{
	}

	Scriptable::~Scriptable()
	{
	}

	const string & Scriptable::getScript() const
	{
		return script;
	}

	void Scriptable::setScript(string script)
	{
		this->script = script;
	}

	int Scriptable::getAvailableMethods() const
	{
		return availableMethods;
	}

	bool Scriptable::isAvailable(int method) const
	{
		if(availableMethods & method) //apparently just returning it causes a performance warning
			return true;
		else
			return false;
	}

	void Scriptable::setAvailableMethods(int availableMethods)
	{
		this->availableMethods = availableMethods;
	}


}// love
