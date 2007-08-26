/**
* @file GameConfiguration.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GameConfiguration.
**/

#ifndef LOVE_GAMECONFIGURATION_H
#define LOVE_GAMECONFIGURATION_H

// LOVE
#include "DisplayMode.h"
#include "Loadable.h"

// STL
#include <string>

// Boost
#include <boost/shared_ptr.hpp>

using std::string;

namespace love
{

	// Forward declarations
	class ConfigLoader;
	class AbstractFile;
	class AbstractImage;

	/**
	* @class GameConfiguration
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GameConfiguration : public Loadable
	{
	protected:

		// title
		string title;

		// author
		string author;

		// thumb
		AbstractImage * thumb;

		// display
		DisplayMode display;

	public:

		/**
		* @brief Contructs an empty GameConfiguration.
		**/
		GameConfiguration();

		/**
		* @brief Destructor.
		**/
		virtual ~GameConfiguration();

		/**
		* @brief Gets title.
		* @return title.
		**/
		const string & getTitle() const;

		/**
		* @brief Sets title.
		* @param title 
		**/
		void setTitle(string title);

		/**
		* @brief Gets author.
		* @return author.
		**/
		const string & getAuthor() const;

		/**
		* @brief Sets author.
		* @param author 
		**/
		void setAuthor(string author);

		/**
		* @brief Gets thumb.
		* @return thumb.
		**/
		AbstractImage * getThumb() const;

		/**
		* @brief Sets thumb.
		* @param thumb 
		**/
		void setThumb(AbstractImage * thumb);

		/**
		* @brief Gets display.
		* @return display.
		**/
		const DisplayMode & getDisplayMode() const;

		/**
		* @brief Sets display.
		* @param display 
		**/
		void setDisplayMode(DisplayMode display);

		/**
		* @brief Loads the configuration from the file.
		* @return LOVE_OK if no errors.
		**/
		virtual int load();

		/**
		* @brief Frees the resources used.
		**/
		void unload();


	};

	typedef boost::shared_ptr<GameConfiguration> pGameConfiguration;

} // love

#endif

