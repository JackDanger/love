#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

using namespace std;

namespace love 
{

	/**
	* @class Resource
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Superclass of all external resources.
	* @todo Actually make this the superclass of all resources.
	**/
	class Resource 
	{
	private:
		string filename;
	public:
		
		/**
		* @brief Creates a new Resource object.
		**/ 
		Resource();

		virtual ~Resource();
	
		/**
		* @brief Loads a file.
		* @param filename The path to the file we want to load.
		**/
		virtual bool load(string filename) = 0;

		/**
		* @brief Returns the filename of this resource.
		* @return The filename of this resource.
		**/
		string getFilename();

	};

}// love

#endif