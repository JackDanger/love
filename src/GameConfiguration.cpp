#include "GameConfiguration.h"
#include "love.h"
#include "Core.h"

#include "AbstractFile.h"
#include "ConfigLoader.h"
#include "AbstractImage.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"

namespace love
{

	GameConfiguration::GameConfiguration()
	{
		// Create the ConfigLoader
		this->thumb = 0;
	}

	GameConfiguration::~GameConfiguration()
	{
		unload();
	}

	const string & GameConfiguration::getTitle() const
	{
		return title;
	}

	void GameConfiguration::setTitle(string title)
	{
		this->title = title;
	}

	const string & GameConfiguration::getAuthor() const
	{
		return author;
	}

	void GameConfiguration::setAuthor(string author)
	{
		this->author = author;
	}

	AbstractImage * GameConfiguration::getThumb() const
	{
		return thumb;
	}

	void GameConfiguration::setThumb(AbstractImage * thumb)
	{
		this->thumb = thumb;
	}

	const DisplayMode & GameConfiguration::getDisplayMode() const
	{
		return display;
	}

	void GameConfiguration::setDisplayMode(DisplayMode display)
	{
		this->display = display;
	}

	int GameConfiguration::load()
	{

		// Get devices
		const AbstractImageDevice & imaging = core->getImaging();
		const AbstractFileSystem & fs = core->getFilesystem();

		this->thumb = imaging.getImage(fs.getBaseFile("data/sys/thumb-std.png"));

		return LOVE_OK;
	}

	void GameConfiguration::unload()
	{
		thumb->unload();
		delete thumb;
	}


}// love
