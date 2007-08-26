#include "GUIGameListElement.h"
#include "GUIGameList.h"
#include "GUIGameList2.h"

#include "GameControlEvent.h"

#include "love.h"
#include "Game.h"

namespace love
{

	/**
	pAbstractImage GUIGameListElement::defaultThumb(new ImageFromFile("data/thumb-std.png"));
	pAbstractImage GUIGameListElement::defaultThumbDither(new ImageFromFile("data/thumb-outer-glow.png"));
	pFont GUIGameListElement::font(new Font("FreeSans.ttf", 22));
	pFont GUIGameListElement::smallFont(new Font("FreeSans.ttf", 11));

	**/

	GUIGameListElement::GUIGameListElement(AbstractImage * defaultThumb, AbstractImage * defaultThumbDither, Font * font, Font * smallFont, AbstractImage * playImage, AbstractImage * stopImage, AbstractImage * restartImage) 
		: defaultThumb(defaultThumb), defaultThumbDither(defaultThumbDither), font(font), smallFont(smallFont), playImage(playImage), stopImage(stopImage), restartImage(restartImage)
	{

		buttonsAlpha = 1.0f;

		defaultThumb = 0;
		defaultThumbDither = 0;
		font = 0;
		smallFont = 0;

		angle = 0;

		initialButtonX = 112;
		initialButtonY = -24;

		buttonPaddingX = 150;
		buttonPaddingY = 30;
		scale = 1.0f;

	}

	GUIGameListElement::~GUIGameListElement()
	{
	}

	Game * GUIGameListElement::getGame()
	{
		return game;
	}

	void GUIGameListElement::setGame(Game * game)
	{
		this->game = game;
	}

	float GUIGameListElement::getScale() const
	{
		return scale;
	}

	void GUIGameListElement::setScale(float scale)
	{
		this->scale = scale;
	}

	void GUIGameListElement::render()
	{
		glPushMatrix();
		
		glTranslatef(getX(), getY(), 0);
		glScalef(scale, scale, 0);

		// Render buttons
		glPushAttrib(GL_CURRENT_BIT);

		glColor4f(1, 1, 1, buttonsAlpha);



		glPushMatrix();
		glTranslatef(initialButtonX, initialButtonY, 0);
		play->render();
		glPopMatrix();

		// Has game already started?
		bool running = this->game->isLoaded();

		if(running)
		{		
			glPushMatrix();
			glTranslatef(initialButtonX + buttonPaddingX, initialButtonY, 0);
			restart->render();
			glPopMatrix();

			glPushMatrix();
			glTranslatef(initialButtonX, initialButtonY + buttonPaddingY, 0);
			stop->render();
			glPopMatrix();
		}

		glPopAttrib();


		glPushMatrix();
		glTranslatef(-GUIGameListElement::defaultThumbDither->getWidth()/2 - 6, -GUIGameListElement::defaultThumbDither->getHeight()/2 - 4, 0);
		GUIGameListElement::defaultThumbDither->render();
		glPopMatrix();


		if(this->game->config->getThumb() != 0)
		{
			glTranslatef(-this->game->config->getThumb()->getWidth()/2, -this->game->config->getThumb()->getHeight()/2, 0);
			game->config->getThumb()->render();
		}
		else
		{
			glTranslatef(-GUIGameListElement::defaultThumb->getWidth()/2, -GUIGameListElement::defaultThumb->getHeight()/2, 0);
			GUIGameListElement::defaultThumb->render();

		}


		glPushMatrix();


			/***
			char buffer[32];
			sprintf(buffer, "%f", orientation);
			string buf(buffer);
			**/



			// Title
			glTranslatef(217, 23, 0);
			font->print(game->config->getTitle());

			// Author
			glTranslatef(1, 20, 0);
			smallFont->print(game->config->getAuthor());


		glPopMatrix();

		glPopMatrix();


		



	}

	void GUIGameListElement::update(float dt)
	{

		// Has game already started?
		bool running = this->game->isLoaded();

		if(buttonsAlpha < 0.2f)
		{
			play->enable = false;
			restart->enable = false;
			stop->enable = false;

		}else
		{
			play->enable = true;

			if(running)
			{
				restart->enable = true;
				stop->enable = true;
			}
		}

		if(running)
		{
			play->setLabel("Resume");

			restart->setX(getX() + initialButtonX + buttonPaddingX);
			restart->setY(getY() + initialButtonY);
			restart->update(dt);

			stop->setX(getX() + initialButtonX);
			stop->setY(getY() + initialButtonY + buttonPaddingY);
			stop->update(dt);
		}
		else play->setLabel("Play");

		
		play->setX(getX() + initialButtonX);
		play->setY(getY() + initialButtonY);
		play->update(dt);



	}

	int GUIGameListElement::load()
	{

		// Play button
		pGameControlEvent cmdPlay(new GameControlEvent(GameControlEvent::PLAY, game->getName()));
		play.reset<GUICircleButton>(new GUICircleButton(playImage, "Play", cmdPlay,  smallFont));
		play->setSize(130,23);
		play->setParent(this);
		play->load();

		// Restart button
		pGameControlEvent cmdRestart(new GameControlEvent(GameControlEvent::RESTART, game->getName()));
		restart.reset<GUICircleButton>(new GUICircleButton(restartImage, "Restart", cmdRestart,  smallFont));
		restart->setSize(130,23);
		restart->setParent(this);
		restart->load();

		// Stop button
		pGameControlEvent cmdStop(new GameControlEvent(GameControlEvent::STOP, game->getName()));
		stop.reset<GUICircleButton>(new GUICircleButton(stopImage, "Stop", cmdStop,  smallFont));
		stop->setSize(130,23);
		stop->setParent(this);
		stop->load();

		return LOVE_OK;
	}

	void GUIGameListElement::unload()
	{
		play->unload();
		restart->unload();
		stop->unload();
	}

	void GUIGameListElement::mousePressed(float x, float y, int button)
	{
		play->mousePressed(x, y, button);
		restart->mousePressed(x, y, button);
		stop->mousePressed(x, y, button);

	}


}// love
