#include "FontTexGame.h"

#include <stdio.h>

#include <SDL.h>

namespace love 
{

	FontTexGame::FontTexGame()
	{
		name = "ftg";
		x = 0;
		y = 0;
	}

	FontTexGame::~FontTexGame()
	{
	}

	bool FontTexGame::load()
	{
		
		img = graphics->getImage("mann.gif");
		img->load();

		font = graphics->getFont("Vera.ttf", 12);
		font->load();

		pImage particle = graphics->getImage("part1.png");
		particle->load();
		
		imgfont = graphics->getImageFont("rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
		imgfont->load();

		psys = graphics->getParticlesystem();
		psys->addColor(255, 255, 255);
		psys->addColor(58, 128, 255, 0, 0);
		psys->setSprite(particle);
		psys->setParticlesPerSecond(100);
		psys->setStartSpeed(300, 400);
		psys->setParticleSize(2, 1);
		psys->setPosition(100, 100);
		psys->setParticleLifetime(1);
		psys->setDirection(0, 360);
		psys->setTangentialAcc(1000);
		psys->setRadialAcc(-2000);

		//sound = audio->getSound("splash.wav");
		//sound->load();
		//sound->play(1);

		//music = audio->getMusic("intermission.mp3");
		//music->load();
		//music->play();

		return true;
	}

	void FontTexGame::unload()
	{
	}

	void FontTexGame::update(float dt)
	{
		x += 100.0f * dt;
		y += 100.0f * dt;

		psys->update(dt);

	}

	void FontTexGame::render()
	{

		psys->render();

		img->render(0, 0, 50, 50);

		graphics->setColor(255,255,0);
		graphics->setFont(font);
		graphics->draw("This is a test. Are we the great testoor?", 100, 100, 200, love::LOVE_ALIGN_CENTER);
		graphics->setFont(imgfont);
		graphics->draw("AReallyLongThingOfDoomOfGayFuck. This is\na\ntest. Are we the great testoor?", x, 100, 100, love::LOVE_ALIGN_RIGHT);
		
		imgfont->print('A', 100, 200);
		
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
