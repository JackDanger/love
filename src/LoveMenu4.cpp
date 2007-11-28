#include "LoveMenu4.h"
#include "GUIGameListElement.h"
#include "Core.h"
#include "love_keys.h"
#include "MessageEvent.h"
#include "GameControlEvent.h"
#include "Game.h"
#include "ConfigLoader.h"

#include <math.h>

#include "love.h"
#include "Core.h"
#include "love_mouse.h"
#include "AbstractFileSystem.h"
#include "AbstractAudio.h"
#include "DisplayMode.h"
#include "GameConfiguration.h"


using boost::dynamic_pointer_cast;



namespace love
{

	LoveMenu4::LoveMenu4()
	{
		this->games = 0;
	}

	LoveMenu4::LoveMenu4(Container<Game> * games)
	{
		this->games = games;
	}

	LoveMenu4::~LoveMenu4()
	{
		delete configLoader;
	}


	int LoveMenu4::init()
	{
		config = new GameConfiguration();
		config->setTitle("LOVE MENU IV");
		config->setAuthor("LOVE DEV Team");

		// Get a reference to the filesystem
		const AbstractFileSystem & fs = core->getFilesystem();
		const DisplayMode & dm = core->getDisplayMode();

		//configLoader = new ConfigLoader(fs.getBase() + "data/love.conf");
		configLoader = core->config.get();

		// Add images
		images["default-thumb"] = core->graphics->getImage("data/sys/thumb-std.png");
		images["default-thumb-dither"] = core->graphics->getImage("data/sys/thumb-outer-glow.png");
		images["button-play"] = core->graphics->getImage("data/sys/button-play.png");
		images["button-stop"] = core->graphics->getImage("data/sys/button-stop.png");
		images["button-restart"] = core->graphics->getImage("data/sys/button-restart.png");
		images["button-cancel"] = core->graphics->getImage("data/sys/button-cancel.png");
		images["logo-small"] = core->graphics->getImage("data/sys/logo128x64.png");
		images["knob-big"] = core->graphics->getImage("data/sys/knob-big.png");
		images["knob-small"] = core->graphics->getImage("data/sys/knob-small.png");
		
		// Add fonts
		fonts["title"] = core->graphics->getFont("data/fonts/FreeSans.ttf", 22);
		fonts["subtitle"] = core->graphics->getFont("data/fonts/FreeSans.ttf", 11);
		fonts["button-font"] = core->graphics->getFont("data/fonts/FreeSans.ttf", 14);

		knob.reset<GUIRadialKnob>(new GUIRadialKnob(images["knob-big"], images["knob-small"], fonts["subtitle"]));
		knob->setPosition(0.1f*dm.getWidth(), dm.getHeight()*0.5f);
		//knob->setControl(&list);

		pMessageEvent msg(new MessageEvent("quit"));
		exit.reset<GUICircleButton>(new GUICircleButton(images["button-cancel"], "Exit to desktop", msg,fonts["subtitle"]));
		exit->setSize(125,23);
		exit->setParent(this);
		exit->setPosition((float)dm.getWidth()-150, 7);

		//text.reset<Text>(new Text());
		list.setParent(this);
		inited = true;

		return LOVE_OK;
	}



	void LoveMenu4::mousePressed(float x, float y, int button)
	{
		switch(button)
		{
		case LOVE_MOUSE_WHEELDOWN:
			//list.setSpeed(list.getSpeed() - 1.2f);
			//list.setAcc(list.getAcc() - 1);
			//list.viewport += list.space_t;
			list.previous(0.1f);
			break;
		case LOVE_MOUSE_WHEELUP:
			//list.setSpeed(list.getSpeed() + 1.2f);
			//list.setAcc(list.getAcc() + 1);
			//list.viewport -= list.space_t;
			
			list.next(0.1f);
			break;
		default:
			break;
		}

		exit->mousePressed(x, y, button);
		list.mousePressed(x, y, button);
		knob->mousePressed(x, y, button);

	}

	void LoveMenu4::mouseReleased(float x, float y, int button)
	{
	}

	void LoveMenu4::keyPressed(int key)
	{

		list.keyPressed(key);


		switch(key)
		{
		case LOVE_KEY_UP:
			list.next();
			break;
		case LOVE_KEY_DOWN:
			list.previous();
			break;
		case LOVE_KEY_LEFT:

			break;
		case LOVE_KEY_RIGHT:

			break;
		case LOVE_KEY_SPACE:
			list.setSpeed(0);
			break;
		case LOVE_KEY_o:
			list.seek(0, 0.5f);
			break;

		}
	}

	void LoveMenu4::eventFired(pEvent e)
	{
		// Change game
		//pMessageEvent pme = dynamic_pointer_cast<MessageEvent, Event>(e);

		//Core::changeGame(pme->getMessage());
		//printf("Event: %s\n", pme->getMessage().c_str());

		if(e->getType() == LOVE_TYPE_GAME_CONTROL_EVENT)
		{
			pGameControlEvent gce = dynamic_pointer_cast<GameControlEvent, Event>(e);
			printf("Game: %s. What: %i\n", gce->getGame().c_str(), gce->getMode());

			Game * g = 0;

			switch(gce->getMode())
			{
			case GameControlEvent::PLAY:

					// Write out to love.conf
					configLoader->addString("last_game", gce->getGame());
					configLoader->write();

					core->startGame(gce->getGame());

					break;
			case GameControlEvent::STOP:
	
				g = core->games[gce->getGame()].get();
				g->stop();

				break;
			case GameControlEvent::RESTART:

				
				g = core->games[gce->getGame()].get();

				if(!g->isLoaded()) 
					break;

				g->unload();

				// Write out to love.conf
				configLoader->addString("last_game", gce->getGame());
				configLoader->write();

				core->startGame(gce->getGame());


				break;
			}
			
		}else if(e->getType() == LOVE_TYPE_MESSAGE_EVENT)
		{
			pMessageEvent mge = dynamic_pointer_cast<MessageEvent, Event>(e);
			
			if(strcmp(mge->getMessage(),"quit") == 0) core->quit();

			//printf("Message: %s\n", mge->getMessage().c_str());
		}

	}

	void LoveMenu4::update(float dt)
	{
		bg.update(dt);

		//bg.center.setX(Core::getMouse()->getX());
		//bg.center.setY(Core::getMouse()->getY());

		//list.viewport = knob->getOrientation();
		
		exit->update(dt);
		list.update(dt);

		// Bg center
		/**
		float r = 150;
		float x = cos(list.getOrientation()) * r;
		float y = sin(list.getOrientation()) * r;
		bg.center.setX(512 + x);
		bg.center.setY(384 + y);
		**/

		//bg.setLine(!list.seeking && list.getSpeed() == 0);

	}



	void LoveMenu4::render()
	{
		bg.render();

		list.render();

		glLoadIdentity();

		glTranslatef(200, 50, 0);
		//text->printf("Speed:%f, Angle: %f, step: %f, size: %i, game:%i",list.getSpeed(),  list.getOrientation(), list.step, list.gameListElements.size());
		glTranslatef(0, 25, 0);
		//text->printf("Seeking: %i, d1: %.2f, d2: %.2f, seekDelta: %.2f, acc: %f.2", list.seeking, list.d1, list.d2, list.seekDelta, list.getAcc());

		//renderText("angle: " + (int)list.getAngle(), 500, 50);

		glLoadIdentity();
		glColor4f(1, 1, 1, 1);
		glTranslatef(exit->getX(), exit->getY(), 0);
		exit->render();

		glTranslatef(15, (float)core->getDisplayMode().getHeight()-68, 0);
		images["logo-small"]->render();

		glLoadIdentity();
		glTranslatef(knob->getX(), knob->getY(), 0);

	}

	int LoveMenu4::load()
	{	
		// Load images
		for(map<string,pAbstractImage>::iterator iter = images.begin();iter!=images.end();iter++)
			iter->second->load();

		// Load fonts
		for(map<string,pAbstractFont>::iterator iter = fonts.begin();iter!=fonts.end();iter++)
			iter->second->load();

		exit->load();

		const DisplayMode & dm = core->getDisplayMode();

		//text->load();
		bg.setSize((float)dm.getWidth(), (float)dm.getHeight());

		Container<Game> games = *this->games;

		list.setParent(this);

		for(games.begin(); !games.end(); games.next())
		{
		
			//printf(" * LOVEMENU IV:  [%s] ... \n", games.key().c_str());

			if(games.key().substr(0, 11) == "love-system")
			{
				//printf(" * !( Skipping ...)");
				continue;
			}
			

			GUIGameListElement e(images["default-thumb"], images["default-thumb-dither"], fonts["title"], fonts["subtitle"], 
				images["button-play"], images["button-stop"], images["button-restart"]);
			e.setGame(games.value().get());

			// Load thumb if neccessary
			pAbstractImage thumb = games.value().get()->config->getThumb();

			if(thumb != 0 && !thumb->isLoaded())
				thumb->load();

			vector<GUIGameListElement> & gle = list.getGameListElements();

			const string & a = games.value()->config->getTitle();

			vector<GUIGameListElement>::iterator iter;

			bool inserted = false;

			for(iter = gle.begin(); iter != gle.end(); iter ++)
			{
				
				const string & b = iter->getGame()->config->getTitle();

				if(a.compare(b) <= 0)
				{
					gle.insert(iter, e);
					inserted = true;
					break;
				}

			}

			if(!inserted)
				gle.push_back(e);

			//list.getGameListElements().push_back(e);
		}

		list.load();


		// Check for last started game.
		//configLoader->load();

		string last_game = "";

		if(configLoader->isString("last_game"))
			last_game = configLoader->getString("last_game");

		if(last_game != "")
		{
			printf("***\n\nFound last game: %s ... exists: ", last_game.c_str());
			bool e = list.seekGame(last_game, 0.75f);
			printf("%i.\n", e);
		}

		loaded = true;
		return LOVE_OK;

	}

	void LoveMenu4::unload()
	{
		exit->unload();

		// Unload images
		// Load images
		for(map<string,pAbstractImage>::iterator iter = images.begin();iter!=images.end();iter++)
			iter->second->unload();

		// Load fonts
		for(map<string,pAbstractFont>::iterator iter = fonts.begin();iter!=fonts.end();iter++)
			iter->second->unload();

		// Unload games.
		list.unload();


		//text->unload();

		//configLoader->unload();

		loaded = false;
	}

	void LoveMenu4::resume()
	{
		Game::resume();
	}

	void LoveMenu4::reloadGraphics()
	{
		
		// Load images
		for(map<string,pAbstractImage>::iterator iter = images.begin();iter!=images.end();iter++)
			iter->second->load();

		// Load fonts
		for(map<string,pAbstractFont>::iterator iter = fonts.begin();iter!=fonts.end();iter++)
			iter->second->load();

		float dw = (float)core->getDisplayMode().getWidth();
		float dh = (float)core->getDisplayMode().getHeight();


		//list.reload();
		bg.setSize(dw,dh);

		list.setSize(dw,dh);

		float div = (5.0f/600.0f) * dh;
		list.setSpacing(1/div);

		exit->setPosition(dw-150, 7);

		/**
		loveBottomRight->load();
		**/

		//text->load();
		
		// Reload all thumbs
		Container<Game> games = *this->games;
		for(games.begin(); !games.end(); games.next())
		{

			pAbstractImage i = games.value()->config->getThumb();

			if(i != 0 && !i->isLoaded())
				i->load();
		}
	}


}// love
