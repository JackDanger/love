#ifndef LOVE_ARGUMENT_CONFIGLOADER_H
#define LOVE_ARGUMENT_CONFIGLOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>

#include "ConfigLoader.h"
#include "AbstractDevice.h"

namespace love
{
	/**
	* @class ArgumentConfigLoader
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-18
	* @brief Special kind of config loader that takes input from the command line.
	**/
	class ArgumentConfigLoader : public ConfigLoader, public AbstractDevice
	{
	private:

		int argc;
		char ** argv;

	public:

		ArgumentConfigLoader(int argc, char * argv[]);

		int init();

		void load();
		void unload();

	};

	typedef boost::shared_ptr<ArgumentConfigLoader> pArgumentConfigLoader;
}

#endif
