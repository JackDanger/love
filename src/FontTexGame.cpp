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
		graphics->push();
		
		graphics->setBackgroundColor(255, 255, 255);
		graphics->setColor(246, 9, 104, 255);
		
		font = graphics->newFont("Vera.ttf", 15); font->load();
		
		img = graphics->newImage("button_pressed.png"); img->load();
		
		graphics->setFont(font);

		return true;
	}

	void FontTexGame::unload()
	{
		graphics->pop();
	}

	void FontTexGame::update(float dt)
	{
	}

	void FontTexGame::render()
	{
		graphics->draw("THIS. IS. PRIMITIVE SHAPES!!!!!!!", 0, 40, 800, love::LOVE_ALIGN_CENTER);
		
		graphics->drawLine(200, 200, -50, 0, 50, 0);
		
		graphics->drawTriangle(400, 200, -50, 50, 50, 50, 0, -50, 2);
		graphics->fillTriangle(600, 200, -50, 50, 50, 50, 0, -50);
		
		graphics->drawQuad(100, 400, -50, 50, -50, -50, 50, -50, 50, 50);
		graphics->fillQuad(300, 400, -50, -50, -50, 50, 50, 50, 50, -50);
		
		graphics->drawCircle(500, 400, 50, 10, 3);
		graphics->fillCircle(700, 400, 50, 30);
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
