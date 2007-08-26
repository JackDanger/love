/**
* @file Loadable.h
* @author Anders Ruud
* @date 2006-09-10
* @brief Contains definition for class Loadable.
**/

#ifndef LOVE_LOADABLE_H
#define LOVE_LOADABLE_H

// LOVE
#include "LoadListener.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{


	/**
	* @class Loadable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-10-28
	* @brief Class from which all loadable resources should inherit.
	* Having a load interface is useful for creating a unified loading system. Also, 
	* try to create the subclass so that as much as possible of the work is done in load().
	**/
	class Loadable
	{

	private:

		// The parent LoadListener that listens for messages.
		LoadListener * parent;

		// A description of what this task is.
		string description;

	protected:

		bool loaded;

	public:

		Loadable();

		virtual ~Loadable();
		
		/**
		* @brief Performs actual task.
		**/
		virtual int load() = 0;

		/**
		* @brief Calls unload, and then load;
		**/
		virtual void reload();

		/**
		* @brief Frees resources
		**/
		virtual void unload() = 0;

		/**
		* @brief Sets the parent LoadListener.
		**/
		void setLoadListener(LoadListener * parent);

		/**
		* @brief Sets the description of the task this Loadable will perform.
		* @param description The task description.
		*
		* For the use of loading screens, etc.
		**/
		void setLoadDescription(string description);

		/**
		* @brief Gets a description for this task.
		* @return A description for this task.
		**/
		const string getLoadDescription() const;

		bool isLoaded() const;

	};

	typedef boost::shared_ptr<Loadable> pLoadable;
}

#endif
