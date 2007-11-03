#include "Loader.h"
#include "Loadable.h"
#include "love.h"

namespace love
{
	Loader::Loader() : completedTasks(0), totalTasks(0)
	{
		setType(LOVE_TYPE_LOADER);
	}

	Loader::Loader(LoadListener * parentLoadListener) : completedTasks(0), totalTasks(0)
	{
		this->parentLoadListener  = parentLoadListener;
		setType(LOVE_TYPE_LOADER);
	}

	Loader::~Loader()
	{
	}



	bool Loader::hasMore()
	{
		return !loadQueue.empty();
	}

	void Loader::loadNext()
	{
		// Return if there are no elements.
		if(!hasMore())
			return;

		// Set descritpion of current task.
		setLoadDescription(loadQueue.front()->getLoadDescription());

		// Complete one task
		completedTasks++;

		// Send description to parent LoadListener.
		loadStateChanged();
			
		// Perform current task
		loadQueue.front()->load();

		// Task done: remove plz
		loadQueue.pop();
	}

	void Loader::add(pLoadable loadable)
	{
		loadQueue.push(loadable);
		totalTasks++;
	}

	const string Loader::getLoadDescription() const
	{
		if(loadQueue.empty())
			return "Done";

		return loadQueue.front()->getLoadDescription();
	}

	float Loader::getProgress() const 
	{
		return ((float)completedTasks/(float)totalTasks);
	}

	void Loader::loadStateChanged()
	{
		if(!hasParent())
			return;

		getParentLoadListener()->loadStateChanged();

	}

	int Loader::load()
	{
		while(hasMore())
			loadNext();

		return LOVE_OK;
	}

	void Loader::unload()
	{

	}



}
