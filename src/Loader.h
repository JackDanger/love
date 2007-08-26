/**
* @file Loader.h
* @author Anders Ruud
* @date 2006-09-10
* @brief Contains definition for class Loader.
**/

#ifndef LOVE_LOADER_H
#define LOVE_LOADER_H


// LOVE
#include "Object.h"
#include "LoadListener.h"
#include "Loadable.h"

// STL
#include <string>
#include <queue>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;
using std::queue;

namespace love 
{

	/**
	* @class Loader
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-10
	* @brief 
	**/
	class Loader : public Object, public Loadable, public LoadListener
	{
	private:

		// Jobs
		queue<pLoadable> loadQueue;

		// 
		int completedTasks;
		int totalTasks;

	public:
		
		Loader();
		Loader(LoadListener * parentLoadListener);
		~Loader();

		bool hasMore();

		void loadNext();

		void add(pLoadable loadable);

		float getProgress() const;

		void loadStateChanged();

		// Overriding
		const string getLoadDescription() const;

		int load();

		void unload();


	};

	typedef boost::shared_ptr<Loader> pLoader;
}

#endif
