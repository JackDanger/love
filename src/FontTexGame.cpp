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
		red.reset<Color>(new Color(255,0,0,255));
		green.reset<Color>(new Color(0,255,0,255));
		blue.reset<Color>(new Color(0,0,255,255));
		
		font = graphics->getFont("Vera.ttf", 8);
		font->load();
		graphics->setFont(font);
		
		imgfont = graphics->getImageFont("rpgfont.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"");
		imgfont->load();
		//graphics->setFont(imgfont);

		pImage up = graphics->getImage("button_default.png"); up->load(); up->setCenter(0, 0);
		pImage down = graphics->getImage("button_pressed.png"); down->load(); down->setCenter(0, 0);
		pImage hover = graphics->getImage("button_hover.png"); hover->load(); hover->setCenter(0, 0);

		button.reset<Button>(new Button("Apply", up, down, hover));
		button->setPosition(300, 300);

		label.reset<Label>(new Label("Img Label"));
		label->setPosition(50, 50);
		label->setBackgroundImage(down);	
		label->adjustSize();
		
		label2.reset<Label>(new Label("left-aligned and padded label"));
		label2->setPosition(175, 50);
		label2->setPadding(10);
		label2->adjustSize();
		label2->setWidth(300);
		label2->setBackgroundColor(green);
		label2->setColor(blue);
		label2->setAlignment(love::LOVE_ALIGN_LEFT);
		label2->setVerticalAlignment(love::LOVE_ALIGN_TOP);

		return true;
	}

	void FontTexGame::unload()
	{
	}

	void FontTexGame::update(float dt)
	{
		r += 90 * dt;
		label->update(dt);
		label2->update(dt);
		button->update(dt);
	}

	void FontTexGame::render()
	{
		label->render();
		label2->render();
		button->render();
	}

	void FontTexGame::keyPressed(int key)
	{
	}

} // love
