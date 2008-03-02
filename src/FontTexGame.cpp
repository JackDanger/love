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
		graphics->setColor(246, 9, 104, 100);
		
		red.reset<Color>(new Color(255,0,0,255));
		green.reset<Color>(new Color(0,255,0,255));
		blue.reset<Color>(new Color(0,0,255,255));
		
		//font = graphics->newFont("Vera.ttf", 15); font->load();
		
		imgfont = graphics->newImageFont("rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\""); imgfont->load();
		
		graphics->setFont(imgfont);
		
		label.reset<Label>(new Label("Assbunny"));
		label->setPosition(100,100);
		//label->setFont(font);
		label->setBackgroundColor(blue);
		label->setColor(red);
		label->adjustHeight();
		label->setWidth(200);
		label->setBorderSize(3);
		//label->setVerticalAlignment(love::LOVE_ALIGN_TOP);

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
		graphics->draw("THIS. IS.\nPRIMITIVE SHAPES!!!!!!!", 0, 40, 800, love::LOVE_ALIGN_CENTER);
		
		graphics->drawLine(200, 200, -50, 0, 50, 0, 2);
		
		graphics->drawTriangle(400, 200, -50, 50, 50, 50, 0, -50, 1);
		graphics->fillTriangle(600, 200, -50, 50, 50, 50, 0, -50);
		
		graphics->drawQuad(100, 400, -50, 50, -50, -50, 50, -50, 50, 50);
		graphics->fillQuad(300, 400, -50, -50, -50, 50, 50, 50, 50, -50);
		
		graphics->drawCircle(500, 400, 50, 10, 3);
		graphics->fillCircle(700, 400, 50, 30);
		
		graphics->setColor(green);
		
		label->render();
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
