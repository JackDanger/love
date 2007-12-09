#include "GameConfigurationLoader.h"
#include "love.h"
#include "Core.h"

#include "AbstractFile.h"
#include "Configuration.h"
#include "AbstractImage.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"

namespace love
{

	GameConfigurationLoader::GameConfigurationLoader(const string & source) : source(source)
	{
		this->title = "Untitled";
		this->author = "Unknown";
	}

	GameConfigurationLoader::~GameConfigurationLoader()
	{
	}

	int GameConfigurationLoader::load()
	{

		if(core->filesystem->exists(source, "game.conf"))
		{

			// Create config loader.
			config = new Configuration(core->filesystem->getFile(source, "game.conf"));

			// Load config
			if(!config->load())
				return LOVE_ERROR;

			// Title, author
			title = config->isString("title") ? config->getString("title") : "Untitled";
			author = config->isString("author") ? config->getString("author") : "Unknown";
			string thumb = config->isString("thumbnail") ? config->getString("thumbnail") : "data/sys/thumb-std.png";

			// Display mode params
			int width = config->isInt("width") ? config->getInt("width") : 800;
			int height = config->isInt("height") ? config->getInt("height") : 600;

			display = core->getDisplayMode();
			display.resize(width, height);

			if(config->isString("thumbnail"))
				this->thumb = core->graphics->getImage(core->filesystem->getFile(source, thumb));
			else if(!config->isString("thumbnail"))
				this->thumb = core->graphics->getImage(thumb);
		}else
		{
			this->thumb = core->graphics->getImage("data/sys/thumb-std.png");
			display = core->getDisplayMode();
		}

		return LOVE_OK;
	}

	void GameConfigurationLoader::unload()
	{
		config->unload();
		delete config;
	}


}// love
