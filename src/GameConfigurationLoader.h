/**
* @file GameConfigurationLoader.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GameConfigurationLoader.
**/

#ifndef LOVE_GAME_CONFIGURATION_LOADER_H
#define LOVE_GAME_CONFIGURATION_LOADER_H

// LOVE
#include "GameConfiguration.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	// Forward declarations
	class Configuration;

	/**
	* @class GameConfigurationLoader
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief Loads a GameConfiguration from a game source.
	**/
	class GameConfigurationLoader : public GameConfiguration
	{
	private:

		// The ConfigLoader used to load all the data below.
		Configuration * config;

		// The source for the game. (Directory or archive file)
		std::string source;

	public:

		/**
		* @brief Contructs an empty GameConfigurationLoader.
		**/
		GameConfigurationLoader(const std::string & source = "");

		/**
		* @brief Destructor.
		**/
		virtual ~GameConfigurationLoader();

		/**
		* @brief Loads the configuration from the file.
		* @return LOVE_OK if no errors.
		**/
		int load();

		/**
		* @brief Frees the resources used.
		**/
		void unload();
	};

	typedef boost::shared_ptr<GameConfigurationLoader> pGameConfigurationLoader;

} // love

#endif

