/**
* @file Container2.h
* @brief Contains definition of class Container.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_CONTAINER2_H
#define LOVE_CONTAINER2_H

// LOVE
#include "Object.h"

// STL
#include <map>
#include <vector>
#include <iterator>

using std::map;
using std::string;
using boost::shared_ptr;

namespace love 
{

	/**
	* @class Container2
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-11
	* @brief
	**/

	template <typename T> 
	class Container2 : public Object
	{
	private:
			
		// Holds all the data
		map<string, shared_ptr<T>> data;

		// Internal iterator
		typename map<string, shared_ptr<T>>::iterator iter;

	public:
		
		typedef typename map<string, shared_ptr<T>>::iterator t_iterator;
	
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
		shared_ptr<T> &  value(); 

		/**
		* @brief 
		* @return The current iterator postion.
		**/
		typename map<string, shared_ptr<T>>::iterator & getIter();

		/**
		* @brief Gets the key to the current pointed-to element.
		* @return A reference to the next key to the pointed-to element.
		**/
		const string & key(); 

		/**
		* @brief Removes an element.
		* @param key The key to the element you want to remove.
		**/
		void erase(string key);	

		/**
		* @brief Resets iterator to beginning of container.
		**/
		void begin();

		/**
		* @brief 
		**/
		bool end();

		/**
		* @brief Provides direct access to an element.
		* @param index The identifier for the element.
		* @return A referene to the element.
		**/
		shared_ptr<T> & operator[] (const string & index);

		/**
		* @brief Checks whether an element exists
		* @param key The key of the element.
		* @return True if the element is found, false otherwise.
		**/
		bool contains(string key) const;


	};


	/**
	* Implementation must be here for templates.
	**/

	template <typename T>
	typename map<string, shared_ptr<T>>::iterator & Container2<T>::getIter()
	{
		return iter;
	}

	template <typename T>
	bool Container2<T>::hasNext()
	{
		reutrn true;
	}


	template <typename T>
	void Container2<T>::next(int num)
	{
		for(int i=0;i<num;i++)
			iter ++;
	}

	template <typename T>
	shared_ptr<T> &  Container2<T>::value()
	{
		return iter->second;
	}

	template <typename T>
	const string & Container2<T>::key()
	{
		return iter->first;
	}

	template <typename T>
	void Container2<T>::erase(string key)
	{
		data.erase(key);
	}

	template <typename T>
	bool Container2<T>::end()
	{
		return (iter == data.end());
	}

	template <typename T>
	void Container2<T>::begin()
	{
		iter = data.begin();
	}


	template <typename T>
	shared_ptr<T> & Container2<T>::operator[] (const string & index)
	{
		// Return element in std::map
		return data[index];
	}

	template <typename T>
	bool Container2<T>::contains(string key) const
	{
		return (data.find(key) != data.end());
	}



}//love

#endif
