#include "LoveMenu3.h"
#include "GUIGameListElement.h"
#include "Core.h"
#include "love_keys.h"
#include "MessageEvent.h"
#include "GameControlEvent.h"
#include "Game.h"

#include <math.h>

using boost::dynamic_pointer_cast;

namespace love
{

	LoveMenu3::LoveMenu3()
	{
		this->games = 0;
	}

	LoveMenu3::LoveMenu3(Container<Game> * games)
	{
		this->games = games;
		setTitle("LÖVE Menu 3rd Gen");
	}

	LoveMenu3::~LoveMenu3()
	{
	}


	void LoveMenu3::init()
	{

		// Add images
		images.create("default-thumb", new ImageFromFile(LoveFile("data/sys","thumb-std.png")));
		images.create("default-thumb-dither", new ImageFromFile(LoveFile("data/sys","thumb-outer-glow.png")));
		images.create("button-play", new ImageFromFile(LoveFile("data/sys","button-play.png")));
		images.create("button-stop", new ImageFromFile(LoveFile("data/sys","button-stop.png")));
		images.create("button-restart", new ImageFromFile(LoveFile("data/sys","button-restart.png")));
		images.create("button-cancel", new ImageFromFile(LoveFile("data/sys","button-cancel.png")));
		images.create("logo-small", new ImageFromFile(LoveFile("data/sys","logo128x64.png")));
		images.create("knob-big", new ImageFromFile(LoveFile("data/sys","knob-big.png")));
		images.create("knob-small", new ImageFromFile(LoveFile("data/sys","knob-small.png")));
		
		// Add fonts
		fonts.create("title", new Font(LoveFile("data/fonts", "FreeSans.ttf"), 22));
		fonts.create("subtitle", new Font(LoveFile("data/fonts", "FreeSans.ttf"), 11));
		fonts.create("button-font", new Font(LoveFile("data/fonts", "FreeSans.ttf"), 14));

		knob.reset<GUIRadialKnob>(new GUIRadialKnob(images["knob-big"].get(), images["knob-small"].get(), fonts["subtitle"].get()));
		knob->setPosition(128, 380);
		knob->setControl(&list);

		pMessageEvent msg(new MessageEvent("quit"));
		exit.reset<GUICircleButton>(new GUICircleButton(images["button-cancel"].get(), "Exit to desktop", msg,fonts["subtitle"].get()));
		exit->setSize(125,23);
		exit->setParent(this);
		exit->setPosition(1024-150, 7);

		text.reset<Text>(new Text());
		list.setParent(this);
		load();
		setInited(true);
	}



	void LoveMenu3::mousePressed(float x, float y, int button)
	{
		switch(button)
		{
		case LOVE_MOUSE_WHEELDOWN:
			list.setSpeed(list.getSpeed() - 1.2f);
			//list.setAcc(list.getAcc() - 1);
			break;
		case LOVE_MOUSE_WHEELUP:
			list.setSpeed(list.getSpeed() + 1.2f);
			//list.setAcc(list.getAcc() + 1);
			break;
		}

		exit->mousePressed(x, y, button);
		list.mousePressed(x, y, button);
		knob->mousePressed(x, y, button);

	}

	void LoveMenu3::mouseReleased(float x, float y, int button)
	{
	}

	void LoveMenu3::keyPressed(int key)
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

	void LoveMenu3::eventFired(pEvent e)
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
					Core::changeGame(gce->getGame().c_str());
					break;
			case GameControlEvent::STOP:
	
				g = Core::getGames()[gce->getGame().c_str()].get();

				if(!g->isInited()) 
					break;

				g->unload();
				g->setInited(false);

				break;
			case GameControlEvent::RESTART:

				g = Core::getGames()[gce->getGame().c_str()].get();

				if(!g->isInited()) 
					break;

				g->reload();
				Core::changeGame(gce->getGame().c_str());

				break;
			}
			
		}else if(e->getType() == LOVE_TYPE_MESSAGE_EVENT)
		{
			pMessageEvent mge = dynamic_pointer_cast<MessageEvent, Event>(e);
			
			if(mge->getMessage() == "quit") Core::quit();

			//printf("Message: %s\n", mge->getMessage().c_str());
		}

	}

	void LoveMenu3::update(float dt)
	{
		bg.update(dt);

		//bg.center.setX(Core::getMouse()->getX());
		//bg.center.setY(Core::getMouse()->getY());



		knob->setOrientation(list.getOrientation());
		knob->update(dt);
		
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



	void LoveMenu3::render()
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

		glTranslatef(15, 700, 0);
		images["logo-small"]->render();

		glLoadIdentity();
		glTranslatef(knob->getX(), knob->getY(), 0);
		knob->render();

	}

	void LoveMenu3::load()
	{
		Game::load();
		
		// Load images
		for(images.begin(); !images.end(); images.next())
			images.value()->load();

		// Load fonts
		for(fonts.begin(); !fonts.end(); fonts.next())
			fonts.value()->load();


		exit->load();

		text->load();
		bg.setSize(1027, 768);

		Container<Game> games = *this->games;

		list.setParent(this);

		for(games.begin(); !games.end(); games.next())
		{
			printf("LOVEMENU III DETECTS [%s] ... \n", games.key().c_str());

			GUIGameListElement e(images["default-thumb"].get(), images["default-thumb-dither"].get(), fonts["title"].get(), fonts["subtitle"].get(), 
				images["button-play"].get(), images["button-stop"].get(), images["button-restart"].get());
			e.setGame(games.value().get());

			list.getGameListElements().push_back(e);
		}

		


		list.load();


	}

	void LoveMenu3::unload()
	{
		Game::unload();

		exit->unload();

		// Unload images
		for(images.begin(); !images.end(); images.next())
			images.value()->unload();

		// Unload fonts
		for(fonts.begin(); !fonts.end(); fonts.next())
			fonts.value()->unload();


		text->unload();
	}

	void LoveMenu3::resume()
	{
		Game::resume();
		//glClearColor((float)94/(float)255, (float)168/(float)255, (float)216/(float)255, (float)255/(float)255);
	}

	void LoveMenu3::reloadGraphics()
	{
		Game::reloadGraphics();

		
		// Load images
		for(images.begin(); !images.end(); images.next())
			images.value()->load();

		// Load fonts
		for(fonts.begin(); !fonts.end(); fonts.next())
			fonts.value()->load();


		list.load();

		/**
		loveBottomRight->load();
		**/

		text->load();
		

		Container<Game> games = *this->games;

		for(games.begin(); !games.end(); games.next())
		{
			if(games.value()->getThumb()!=0)
				games.value()->getThumb()->load();
		}
	}


}// love
