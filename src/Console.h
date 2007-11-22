/**
* @file Console.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class Console.
**/

#ifndef LOVE_CONSOLE_H 
#define LOVE_CONSOLE_H 

// LOVE
#include "AbstractEntity.h"
#include "Loadable.h"

// STL
#include <deque>
#include <string>

using std::deque;
using std::string;

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	class Font;

	/**
	* @class Console
	* @version 1.0
	* @since 1.0
	* @author 
	* @date 2007-08-19
	* @brief 
	**/
	class Console : public AbstractEntity, public Loadable
	{
	private:

		bool compact;

		bool visible;
	
		// The queue containing the actual messages
		deque<string> messages;

		// The font used for rendering the messages
		Font * font;

		// The size of the message queue
		unsigned int size;

	public:
	
		// Friends
		friend class Core;

		/**
		* @brief Constructs an empty Console.
		**/
		Console(unsigned int size = 10);
		
		/**
		* @brief Destructor.
		**/
		virtual ~Console();

		void update(float dt);
		void render();

		int load();
		void unload();

		void setSize(unsigned int size);
		unsigned int getSize();

		void push(string message);

		
	}; // Console
	
	typedef boost::shared_ptr<Console> pConsole;
	
} // love

#endif
