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
		r = 0;
	}

	FontTexGame::~FontTexGame()
	{
	}

	bool FontTexGame::load()
	{
		
		img = graphics->getImage("Explosion_1.png");
		img->load();

		animation.reset<Animation>(new Animation(img, 96, 96, 0.1f));
		animation->setMode(LOVE_ANIMATION_BOUNCE);
		//animation->setMode(LOVE_ANIMATION_LOOP);
		animation->setCenter(-50, -50);

		return true;
	}

	void FontTexGame::unload()
	{
	}

	void FontTexGame::update(float dt)
	{
		animation->update(dt);
		r += 90 * dt;
	}

	void FontTexGame::render()
	{
		animation->render(200, 200, r, 1, 1);		
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
