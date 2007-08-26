#ifndef LOVE_PARAMETERS_H
#define LOVE_PARAMETERS_H

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

#include "AbstractDevice.h"

using std::map;
using std::string;

namespace love
{
	

	/**
	* @class Parameters
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-18
	* @brief Keeps track of the program parameters from the command line.
	**/
	class Parameters : public AbstractDevice
	{
	private:

		int argc;
		char ** argv;

		map<string, string> data;

	public:

		Parameters(int argc, char ** argv);
		int init();

		bool exists(string key);
		string get(string key);

	};

	typedef boost::shared_ptr<Parameters> pParameters;
}

#endif
