#include "Loadable.h"

namespace love
{
	Loadable::Loadable() : loaded(false)
	{
	}

	Loadable::~Loadable()
	{
	}
	
	void Loadable::reload()
	{
		this->unload();
		this->load();
	}

	void Loadable::setLoadListener(LoadListener * parent)
	{
		this->parent = parent;
	}

	void Loadable::setLoadDescription(string description)
	{
		this->description = description;
	}

	const string Loadable::getLoadDescription() const
	{
		return description;
	}

	bool Loadable::isLoaded() const
	{
		return loaded;
	}

}
