/**
* @file Printable.h
* @brief Contains definition of class Printable.
* @date 2006-03-10
* @author Anders Ruud
**/

#ifndef AMF_PRINTABLE_H
#define AMF_PRINTABLE_H

#include <string>

using std::string;

namespace love
{
	

	/**
	* @class Printable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-10
	* @brief Every class that can be converted into 
	* a string should inherit from this class.
	**/
	class Printable
	{
		private:

			string str;

		public:
			Printable();
			Printable(std::string str);
			virtual ~Printable();

			/**
			* @brief Returns a string representation of an object.
			* @return A string representation of an object.
			**/
			virtual string toString();

	};

}

#endif
