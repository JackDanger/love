#include "GameConfiguration.h"
#include "love.h"
#include "Core.h"

#include "AbstractFile.h"
#include "Configuration.h"
#include "AbstractImage.h"
#include "AbstractImageDevice.h"
#include "AbstractFileSystem.h"

using std::string;

namespace love
{

	GameConfiguration::GameConfiguration()
	{
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

	bool GameConfiguration::getDisableEscape()
	{
		return disableEscape;
	}

	void GameConfiguration::setDisableEscape(bool setting)
	{
		this->disableEscape = setting;
	}

	pAbstractImage GameConfiguration::getThumb() const
	{
		return thumb;
	}

	void GameConfiguration::setThumb(pAbstractImage thumb)
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

		this->thumb = core->graphics->getImage("data/sys/thumb-std.png"); 
		return LOVE_OK;
	}

	void GameConfiguration::unload()
	{
	}


}// love
