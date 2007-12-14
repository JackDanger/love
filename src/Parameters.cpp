#include "Parameters.h"
#include "love.h"

using std::string;

namespace love
{
	Parameters::Parameters(int argc, char ** argv) : argc(argc)
	{
		this->argv = argv;
	}


	int Parameters::init()
	{
		
		int i = 0;

		// Loop though each
		while( i < argc )
		{
			if(i == 0)
			{
				// Add the 0-param as "exe". 
				data["exe"] = string(argv[0]);
				i++;
				continue;
			}

			// 2 more means an app switch
			if((i+2) <= argc)
			{
				// Add each paired parameter as an entry
				data[string(argv[i])] = string(argv[i+1]);
				i += 2;
				continue;
			}
			else if((i+1) <= argc)
			{
				// The user may supply one game via the command line arguments.
				data["game"] = string(argv[i]);
			}

			i++;
			
		}
		return LOVE_OK;
	}

	bool Parameters::exists(string key)
	{
		return (data.count(key) != 0);
	}

	string Parameters::get(string key)
	{
		return exists(key) ? data[key] : "";
	}


}
