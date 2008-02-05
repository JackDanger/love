#include "NoGame.h"

#include "using_graphics.h"
#include "love_version.h"

#include "love_math.h"
#include "resources.h"
#include <cmath>

namespace love 
{

	NoGame::NoGame()
	{
		name = "NoGame";
		flashi = 0.6f;
		flashb = 0;
		render_nogame = true;
	}

	NoGame::~NoGame()
	{
	}

	bool NoGame::load()
	{
		moose_angle = 0;

		graphics->push();
		graphics->setBackgroundColor(0, 138, 255);
		graphics->setColor(255, 255, 255, 255);
		
		big = graphics->newFont(Vera_ttf, 15); big->load();
		small = graphics->newFont(Vera_ttf, 10); small->load();
		

		logo_big = graphics->newImage(logo256x128_png); logo_big->load();
		logo_small = graphics->newImage(logo128x64_png); logo_small->load();
		mini_moose = graphics->newImage(mini_moose_png); mini_moose->load();

		graphics->setColor(255, 255, 255, 255);

		return true;
	}

	void NoGame::unload()
	{
		graphics->pop();
	}

	void NoGame::update(float dt)
	{
		moose_angle += pi * dt;
		flashb += dt;
		if(flashb >= flashi)
		{
			render_nogame = !render_nogame;
			flashb = 0;
		}
	}

	void NoGame::render()
	{
		float width = (float)graphics->getWidth();
		float height = (float)graphics->getHeight();

		// Render mini-moose.
		float my = height/2.0f + sin(moose_angle) * 10;
		float mx = width/2.0f;

		mini_moose->render(mx, my + 65);

		logo_big->render(width/2.0f, height/2.0f - 30);
		
		

		if(render_nogame)
		{
			graphics->setFont(big);
			graphics->draw("No Game", (width-300)/2.0f, height/2.0f + 200, 300, LOVE_ALIGN_CENTER);
		}

		graphics->setFont(small);
		//graphics->draw("To run games, locate a .love file and open it with the love executable.", (width-300)/2.0f, height/2.0f + 250, 300, LOVE_ALIGN_CENTER);

		std::string s = "";
		s += version_string();
		s += "\nMini-Moose";
		graphics->draw(s.c_str(), width - 210, height - 35, 200,  LOVE_ALIGN_RIGHT);
	}

	void NoGame::keyPressed(int key)
	{
	}

} // love
