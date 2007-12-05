#ifndef LOVE_DEFAULT_CONFIGURATION_H
#define LOVE_DEFAULT_CONFIGURATION_H

#include "ConfigLoader.h"
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
		DefaultConfiguration();
		~DefaultConfiguration();

		virtual void defaultSystemConfig(const pConfigLoader & config);
		virtual void defaultGameConfig(const pConfigLoader & config);
	};

	typedef boost::shared_ptr<DefaultConfiguration> pDefaultConfiguration;
}

#endif