#include "LoadListener.h"

namespace love
{
	LoadListener::LoadListener() : parentLoadListener(0)
	{
	}

	LoadListener::~LoadListener()
	{
	}

	bool LoadListener::hasParent() const
	{
		return parentLoadListener != 0;
	}

	LoadListener * LoadListener::getParentLoadListener()
	{
		return this->parentLoadListener;
	}

	void LoadListener::setParentLoadListener(LoadListener * loadListener)
	{
		this->parentLoadListener = loadListener;
	}
}
