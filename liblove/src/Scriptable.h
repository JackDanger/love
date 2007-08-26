/**
* @file Scriptable.h
* @author Anders Ruud
* @date 2006-11-23
* @brief Contains definition for class Scriptable.
**/

#ifndef LOVE_SCRIPTABLE_H
#define LOVE_SCRIPTABLE_H

// LOVE
#include "love_globals.h"

// STL
#include <string>
using std::string;

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Scriptable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-23
	* @brief 
	**/
	class Scriptable
	{
	private:

		// script
		string script;

		// availableMethods
		int availableMethods;

	public:

		/**
		* @brief Contructs an empty Scriptable.
		**/
		Scriptable();
		virtual ~Scriptable();

		/**
		* @brief Gets script.
		* @return script.
		**/
		const string & getScript() const;


		/**
		* @brief Sets script.
		* @param script 
		**/
		void setScript(string script);


		/**
		* @brief Gets availableMethods.
		* @return availableMethods.
		**/
		int getAvailableMethods() const;

		/**
		* @brief Cheks if a certain method is available.
		* @return True if available, false otherwise.
		**/
		bool isAvailable(int method) const;


		/**
		* @brief Sets availableMethods.
		* @param availableMethods 
		**/
		void setAvailableMethods(int availableMethods);


	};

	typedef boost::shared_ptr<Scriptable> pScriptable;

} // love

#endif

