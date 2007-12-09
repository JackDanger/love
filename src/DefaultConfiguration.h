#ifndef LOVE_DEFAULT_CONFIGURATION_H
#define LOVE_DEFAULT_CONFIGURATION_H

#include "Configuration.h"
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* @class DefaultConfiguration
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-12-05
	* @brief Contains the default configuration information that is to be entered into the
			 variuous ConfigLoader lists. Contained in this class for easy manipulation.
	**/
	class DefaultConfiguration
	{
	protected:
	public:
		/**
		 * @brief Constructor. Does nothing.
		 **/
		DefaultConfiguration();

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~DefaultConfiguration();

		/**
		 * @param config A ConfigLoader object to be manipulated.
		 * @brief Adds the default system configurations to the passed ConfigLoader object.
		 **/
		virtual void defaultSystemConfig(const pConfiguration & config);

		/**
		 * @param config A ConfigLoader object to be manipulated.
		 * @brief Adds the default game configurations to the passed ConfigLoader object.
		 **/
		virtual void defaultGameConfig(const pConfiguration & config);
	};

	typedef boost::shared_ptr<DefaultConfiguration> pDefaultConfiguration;
}

#endif
