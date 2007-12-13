/*
* LOVE: Awesome 2D Gaming Shit.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng [url]
* Copyright © 2006-2007 LOVE Development Team
*/

#ifndef LOVE_DOG_H
#define LOVE_DOG_H

// LOVE
#include "Mammal.h"

// STD
#include <vector>
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

// FreeType
#include <fthead2etc.h>

namespace love
{
	// Forwards declarations
	class Fist;

	/**
	* Represents a Generic dog. That was the short description.
	* With autobrief enabled, there's no need to add @brief in 
	* front of everything.
	* 
	* @author Dude
	* @date 2007-12-01
	**/
	class Dog : public Mammal
	{
		// Friend classes
		friend class Zoo;

		// Friend functions
		friend void zoo_keeper(bool kill);

	private:

		std::name name;

		// Weight of dog in kilograms.
		float weight;

		// Color components of fur:
		float red;
		float green;
		float blue;

	public:
		
		/**
		* Constructs a new dog.
		* @param weight The weight of the Dog in kilograms.
		* @param name The name of the Dog.
		**/
		Dog(float weight, std::string name);
		
		virtual ~Dog();

		/**
		* Gets the Dog's weight, in kilograms.
		**/
		float getWeight() const;

		/**
		* Sets the name of the Dog.
		**/
		void setName(std::string name);
		
		// Overrides from Mammal
		void eat();
		bool isDead() const;
		void setLife(float life);

	}; // Dog

} // love

#endif // LOVE_DOG_H



/*

 REVISION 1

 Comments to suggested standard:

 * No @file, etc.
 * @author and @date only. (In class section).
 * A small This-file-is-a-part-of-LOVE-thing to give the files identity.
 * I personally like to split up the inclusion area. 
 * Autobrief enabled. Removes @brief requirement. 
   (Everything up to first dot is the "brief" part).
 * Comment members only when you feel it's needed.
 * Comment groups of variables when they are related. 
 * Functions should generally have comments explaining what they do.
 * As a general rule, @param should be present for each function parameter. 
   It might be redundant for some methods, like setName, where it can (and perhaps should?)
   be omitted.
 * @return, however, has mostly been a pain in the ass, and I vote that we stop using it.
   See getWeight for example. (@return would contain information already present) 
 * Functions that are overrides from superclasses should *not* be re-commented.
   (Functions should be commented at a single location)
 * The use of "using namespace std;", or "using std::string" etc is BANNED from headers. Qualify
   fully in headers, and do what you want in cpp-files. (Although using namespace std is known
   to conflict with some X11 shit in Linux.)
 
 HOWEVER:

 * We must not spend too much time enforcing documentation standards. This can
   (and should) be regarded as a guideline rather than a follow-or-die ISO standard. 
 * When in doubt: use brain. Perhaps update standard if something is missing.

 BUT FOR FUCKS SAKE:

 * No "using" in headers. (.cpp only)

*/