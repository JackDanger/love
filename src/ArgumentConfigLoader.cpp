#include "ArgumentConfigLoader.h"
#include "love.h"

namespace love
{
	ArgumentConfigLoader::ArgumentConfigLoader(int argc, char ** argv) : argc(argc)
	{
		this->argv = argv;
	}

	int ArgumentConfigLoader::init()
	{
		
		load();

		return LOVE_OK;
	}

	int ArgumentConfigLoader::load()
	{
	
		int i = 0;

		// Loop though each
		while( i < argc )
		{
			if(i == 0)
			{
				printf("# Base: %s\n", argv[0]);
				i++;
				continue;
			}

			// 2 more means an app switch
			if((i+2) <= argc)
			{
				printf("%s %s\n", argv[i], argv[i+1]);
				i += 2;
				continue;
			}
			else if((i+1) <= argc)
			{
				printf("game: %s\n", argv[i]);
			}

			i++;
			//printf(" ### Arg: %s\n", argv[i]);
			
		}

		//std::string str(argv[1]);

		return LOVE_OK;
	}

}
