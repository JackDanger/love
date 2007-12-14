#include "GameConfigurationLoader.h"
#include "love.h"
#include "Core.h"

#include "AbstractFile.h"
#include "Configuration.h"
#include "AbstractImage.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"
#include "DefaultConfiguration.h"

using std::string;

namespace love
{

	GameConfigurationLoader::GameConfigurationLoader(const string & source) : source(source)
	{
		this->title = "Untitled";
		this->author = "Unknown";
		this->disableEscape = false;
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

			pDefaultConfiguration defaultConfig(new DefaultConfiguration());
			defaultConfig->defaultGameConfig(config); // load defaults

			// Load config
			if(!config->load())
				return LOVE_ERROR;

			/*

			// Title, author
			title = config->isString("title") ? config->getString("title") : "Untitled";
			author = config->isString("author") ? config->getString("author") : "Unknown";
			string thumb = config->isString("thumbnail") ? config->getString("thumbnail") : "data/sys/thumb-std.png";

			// Display mode params
			int width = config->isInt("width") ? config->getInt("width") : 800;
			int height = config->isInt("height") ? config->getInt("height") : 600;

			*/

			// Title, author
			title = config->getString("title");
			author = config->getString("author");
			string thumb = config->getString("thumbnail");

			// Display mode params
			int width = config->getInt("width");
			int height = config->getInt("height");

			// "Consume" escape key?
			disableEscape = config->getBool("disable_escape");

			display = core->getDisplayMode();
			display.resize(width, height);

			if(thumb != "data/sys/thumb-std.png")
				this->thumb = core->graphics->getImage(core->filesystem->getFile(source, thumb));
			else if(thumb == "data/sys/thumb-std.png")
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
