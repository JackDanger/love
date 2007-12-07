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

	void DefaultConfiguration::defaultSystemConfig(const pConfigLoader & config)
	{
		// General
		config->addBool("verbose", false);
		config->addInt("console_lines", 30);

		// Video
		config->addBool("fullscreen", false);
		config->addBool("vsync", true);
		config->addString("default_resolution", "800x600");
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

	void DefaultConfiguration::defaultGameConfig(const pConfigLoader & config)
	{
	}
}
