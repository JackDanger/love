/**
* @file Keyboard.h
* @brief Contains definition of class Keyboard.
* @date 2006-03-12
* @author Anders Ruud
**/

#ifndef LOVE_KEYBOARD_H
#define LOVE_KEYBOARD_H

#include "KeyListener.h"
#include "AbstractDevice.h"

namespace love
{


	/**
	* @class Keyboard
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-12
	* @brief Can be used to keep track of the keyboard state.
	**/
	class Keyboard : public AbstractDevice, public KeyListener
	{
	private:

		// The number of key states we need to 
		// represent the state on a keyboard.
		const static int NUM_KEYS = 1024;

		// Our keyboard state.
		bool keys[NUM_KEYS];

	public:


		/**
		* @brief Creates a new Keyboard object.
		**/
		Keyboard();
		~Keyboard();

		/**
		* @brief Inits the Keyboard.
		**/
		int init();

		/**
		* @brief Changes the state of the keyboard.
		* @param key The ASCII keycode of the pressed key.
		**/
		void keyPressed(int key);

		/**
		* @brief Changes the state of the keyboard.
		* @param key The ASCII keycode of the released key.
		**/
		void keyReleased(int key);

		/**
		* @brief Checks whether a key is currently down.
		* @param key The keycode of the key we want to check.
		* @return True if the key is down, false otherwise.
		**/
		bool isDown(int key);
	};

	typedef boost::shared_ptr<Keyboard> pKeyboard;

}// love

#endif
