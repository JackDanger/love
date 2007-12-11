#include "DefaultConfiguration.h"
#include "Core.h"
#include "love.h"
#include "AbstractFileSystem.h"

namespace love
{
	DefaultConfiguration::DefaultConfiguration()
	{}

	DefaultConfiguration::~DefaultConfiguration()
	{}

	void DefaultConfiguration::defaultSystemConfig(const pConfiguration & config)
	{
		defaultSystemConfig(config.get());
	}

	void DefaultConfiguration::defaultSystemConfig(Configuration * config)
	{
		// General
		config->addBool("verbose", false);
		config->addInt("console_lines", 30);
		config->addBool("copy_game", false); // wether to copy an externally opened game to the game directory

		// Video
		config->addString("default_resolution", "800x600");
		config->addInt("color_depth", 32);
		config->addBool("fullscreen", false);
		config->addBool("vsync", true);
		config->addInt("FSAA", 0);

		// Audio
		config->addInt("audio_quality", 44100);
		config->addInt("audio_latency", 2048);
		config->addInt("music_volume", 100);
		config->addInt("sound_volume", 100);
		config->addBool("mute", false);

		// Paths (these should be changed for release)
		config->addString("config_path", core->getFilesystem().getBase() + "data/love.config");
		config->addString("resource_path", core->getFilesystem().getBase() + "data/love.data");
		config->addString("gamedir", core->getFilesystem().getBase() + "data/games");
	}

	void DefaultConfiguration::defaultGameConfig(const pConfiguration & config)
	{
		defaultGameConfig(config.get());
	}

	void DefaultConfiguration::defaultGameConfig(Configuration * config)
	{
		// General
		config->addString("title", "Untitled");
		config->addString("author", "Unknown");
		config->addString("love_version", "0.3");
		config->addBool("disable_escape", false);

		// Video
		config->addInt("width", 800);
		config->addInt("height", 600);

		// Thumbnail
		config->addString("thumbnail", "data/sys/thumb-std.png");
	}
}
