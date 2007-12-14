/**
* @file Loader.h
* @author Anders Ruud
* @date 2006-09-09
* @brief Contains definition for class LoadListener.
**/

#ifndef LOVE_LOAD_LISTENER
#define LOVE_LOAD_LISTENER

// LOVE
#include "Listener.h"

// STL
//#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love 
{

	/**
	* @class LoadListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-09
	* @brief
	**/
	class LoadListener : public Listener
	{
	protected:
	
		// The parent listener
		LoadListener * parentLoadListener;

	public:
		
		LoadListener();

		virtual ~LoadListener();

		LoadListener * getParentLoadListener();

		void setParentLoadListener(LoadListener * loadListener);

		bool hasParent() const;

		virtual void loadStateChanged() = 0;



	};

	typedef boost::shared_ptr<LoadListener> pLoadListener;
	
}

#endif
