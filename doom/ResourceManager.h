/**
* @file ResourceManager.h
* @brief Contains definition of class ResourceManager.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_RESOURCE_MANAGER_H
#define LOVE_RESOURCE_MANAGER_H

// LOVE
#include "Object.h"

// STL
#include <map>
#include <vector>
#include <iterator>

using std::vector;
using std::map;

namespace love 
{


	/**
	* @class ResourceManager
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Provides simple, easy management for a resource.
	*
	* Can contain anything which inherits from Identifiable.
	**/

	template <typename T> 
	class ResourceManager : public Object
	{
	private:
		
	public:

		map<int, T> resources;

		int add(T t);

		void unlink(int id);

		void remove(int id);

		T get(int id);

		void clear();

		void clearElementsOnly();

		const std::map<int, T> & getMap() const;

		bool contains(int id) const;

	};


	/**
	* Implementation must be here for templates.
	**/

	template <typename T> 
	int ResourceManager<T>::add(T t)
	{
		resources[t->getId()] = t;
		return t->getId();
	}

	template <typename T>
	void ResourceManager<T>::unlink(int id)
	{
		// Delete memory
		delete resources[id];

	}	

	template <typename T>
	void ResourceManager<T>::remove(int id)
	{
		// Remove entry from map
		resources.erase(id);
	}

	template <typename T>
	T ResourceManager<T>::get(int id)
	{
		return resources[id];
	}

	template <typename T>
	void ResourceManager<T>::clear()
	{
		for each( pair<int, T> p in resources )
			delete p.second;
		
		resources.clear();

	}

	template <typename T>
	void ResourceManager<T>::clearElementsOnly()
	{
		resources.clear();
	}

	template <typename T>
	const std::map<int, T> & ResourceManager<T>::getMap() const
	{
		return resources;
	}

	template <typename T>
	bool ResourceManager<T>::contains(int id) const
	{
		return (resources.end() != resources.find(id));
	}


}//love

#endif
