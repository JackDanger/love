/**
* @file GameControlEvent.h
* @author Anders Ruud
* @date 2007-05-25
* @brief Contains definition for class GameControlEvent.
**/

#ifndef LOVE_GAMECONTROLEVENT_H
#define LOVE_GAMECONTROLEVENT_H

// LOVE
#include "Event.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{

	/**
	* @class GameControlEvent
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-25
	* @brief 
	**/
	class GameControlEvent : public Event
	{
	private:

		// mode
		int mode;

		// game
		string game;

	public:

		static const int PLAY = 0;
		static const int STOP = 1;
		static const int RESTART = 2;

		/**
		* @brief Contructs an empty GameControlEvent.
		**/
		GameControlEvent(int mode, const string & game);
		virtual ~GameControlEvent();

		/**
		* @brief Gets mode.
		* @return mode.
		**/
		int getMode() const;


		/**
		* @brief Sets mode.
		* @param mode 
		**/
		void setMode(int mode);


		/**
		* @brief Gets game.
		* @return game.
		**/
		const string & getGame() const;


		/**
		* @brief Sets game.
		* @param game 
		**/
		void setGame(string game);


	};

	typedef boost::shared_ptr<GameControlEvent> pGameControlEvent;

} // love

#endif

