#include "love_arg.h"

using std::string;

namespace love
{

	string get_arg_game(int argc, char* argv[])
	{
		string s;

		if(argc <= 1) return s;

		// Next-to-last element must not be an option flag.
		if(is_arg_option(argc, argv, argc-2))
			return s;

		s = string(argv[argc-1]);
		return s;
	}

	string get_arg(int argc, char* argv[], const string & attribute)
	{
		string s;

		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i], attribute.c_str()) == 0 && i+1<argc)
			{
				s = string(argv[i+1]);
				break;
			}
		}

		return s;
	}

	bool is_arg_option(int argc, char* argv[], int index)
	{
		if(index >= argc)
			return false;

		string arg = string(argv[index]);

		// Find hyphens.
		string::size_type loc = arg.find("-", 0);

		if(loc == string::npos || loc > 1)
			return false;

		return true;
	}

	bool is_arg_absolute(const std::string path)
	{
#ifdef WIN32
		std::string s = path.substr(1, 2);
		return (s == ":\\" || s == ":/");
#else
		std::string s = path.substr(0, 1);
		return (s == "/");
#endif
	}

} // love
