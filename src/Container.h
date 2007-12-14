/**
* @file Container.h
* @brief Contains definition of class Container.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_CONTAINER_H
#define LOVE_CONTAINER_H

// LOVE
#include "Object.h"

// STL
#include <map>
#include <vector>
#include <iterator>

namespace love 
{

	/**
	* @class Container
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-11
	* @brief
	**/

	template <class T> 
	class Container : public Object
	{
	private:

		// Holds all the data
		std::map<std::string, boost::shared_ptr<T> > data;

		// Internal iterator
		typename std::map<std::string, boost::shared_ptr<T> >::iterator iter;

	public:
		
		typedef typename std::map<std::string, boost::shared_ptr<T> >::iterator t_iterator;
	
		/**
		* @brief Checks whether the next iterated element exists.
		* @return Whether the next iterated element exists.
		**/
		bool hasNext();

		/**
		* @brief Iterates to the next element.
		* This method will not check if there actually IS a "next" element.
		* @param num The number of elements to progress.
		* @see hasNext();
		**/
		void next(int num = 1);

		/**
		* @brief Gets the current pointed-to element;
		* @return A reference to the next pointed-to element.
		**/
		boost::shared_ptr<T> &  value(); 

		/**
		* @brief Gets the underlying pointer of the current pointed-to element.
		* @return A pointer to the current element.
		**/
		T * v();

		/**
		* @brief 
		* @return The current iterator postion.
		**/
		typename std::map<std::string, boost::shared_ptr<T> >::iterator & getIter();

		/**
		* @brief Gets the key to the current pointed-to element.
		* @return A reference to the next key to the pointed-to element.
		**/
		const std::string & key(); 

		/**
		* @brief Gets the key to the current pointed-to element as a char array.
		* @return The key to the pointed-to element.
		**/
		const char * k(); 

		/**
		* @brief Removes an element.
		* @param key The key to the element you want to remove.
		**/
		void erase(const std::string & key);

		/**
		* @brief Removes all elements.
		**/
		void clear();	

		/**
		* @brief Resets iterator to beginning of container.
		**/
		void begin();

		/**
		* @brief 
		**/
		bool end();

		/**
		* @brief Same thing as end(), only inverted bool.
		**/
		bool hasMore();

		/**
		* @brief Provides direct access to an element.
		* @param key The identifier for the element.
		* @return A referene to the element.
		**/
		boost::shared_ptr<T> & operator[] (const std::string & key);

		/**
		* @brief Checks whether an element exists
		* @param key The key of the element.
		* @return True if the element is found, false otherwise.
		**/
		bool contains(const std::string & key) const;

		/**
		* @brief Provides direct access to an element.
		* @param t A pointer to the new element.
		* @return A referene to the new element.
		**/
		boost::shared_ptr<T> & create(const std::string & key, T * t);

		int size() const;


	};

	/**
	* Implementation must be here for templates.
	**/

	template <class T>
	typename std::map<std::string, boost::shared_ptr<T> >::iterator & Container<T>::getIter()
	{
		return iter;
	}

	template <class T>
	bool Container<T>::hasNext()
	{
		return true;
	}


	template <class T>
	void Container<T>::next(int num)
	{
		for(int i=0;i<num;i++)
			iter ++;
	}

	template <class T>
	boost::shared_ptr<T> &  Container<T>::value()
	{
		return iter->second;
	}

	template <class T>
	T * Container<T>::v()
	{
		return iter->second.get();
	}

	template <class T>
	const std::string & Container<T>::key()
	{
		return iter->first;
	}

	template <class T>
	const char * Container<T>::k()
	{
		return iter->first.c_str();
	}

	template <class T>
	void Container<T>::erase(const std::string & key)
	{
		data.erase(key);
	}

	template <class T>
	void Container<T>::clear()
	{
		data.clear();
	}

	template <class T>
	bool Container<T>::end()
	{
		return (iter == data.end());
	}

	template <class T>
	bool Container<T>::hasMore()
	{
		return (iter != data.end());
	}

	template <class T>
	void Container<T>::begin()
	{
		iter = data.begin();
	}


	template <class T>
	boost::shared_ptr<T> & Container<T>::operator[] (const std::string & key)
	{
		// Return element in std::map
		return data[key];
	}

	template <class T>
	bool Container<T>::contains(const std::string & key) const
	{
		return (data.find(key) != data.end());
	}

	
	template <class T>
	boost::shared_ptr<T> & Container<T>::create(const std::string & key, T * t)
	{
		
		if(t == 0)
		{
			// gcc ... what trickery (syntax) is this?
			//this->data[key].template reset<T>(new T());
			//data[key]->name = key;
			//return data[key];
			printf("Warning: trying to add null pointer to container.");
		}

		data[key].template reset<T>(t);
		data[key]->name = key;
		return data[key];
		
	}
	
	template <class T>
	int Container<T>::size() const
	{
		return (int)data.size();
	}



}//love

#endif
