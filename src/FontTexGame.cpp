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
		
		font = graphics->getFont("Vera.ttf", 8);
		font->load();
		graphics->setFont(font);

		pImage up = graphics->getImage("button_default.png"); up->load(); up->setCenter(0, 0);
		pImage down = graphics->getImage("button_pressed.png"); down->load(); down->setCenter(0, 0);
		pImage hover = graphics->getImage("button_hover.png"); hover->load(); hover->setCenter(0, 0);

		button.reset<Button>(new Button("Apply", up, down, hover));
		button->setPosition(300, 300);

		label.reset<Label>(new Label("Tesitng teh label"));
		label->setPosition(50, 50);

		return true;
	}

	void FontTexGame::unload()
	{
	}

	void FontTexGame::update(float dt)
	{
		r += 90 * dt;
		label->update(dt);
		button->update(dt);
	}

	void FontTexGame::render()
	{
		label->render();
		button->render();
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
