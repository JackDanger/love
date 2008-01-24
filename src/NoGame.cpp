#include "NoGame.h"

#include "using_graphics.h"
#include "love_version.h"

namespace love 
{

	NoGame::NoGame()
	{
		name = "NoGame";
	}

	NoGame::~NoGame()
	{
	}

	bool NoGame::load()
	{
		graphics->push();
		graphics->setBackgroundColor(0, 0, 0);
		graphics->setColor(255, 255, 255, 255);
		
		big = graphics->newFont("Vera.ttf", 15); big->load();
		small = graphics->newFont("Vera.ttf", 10); small->load();


		color.reset<AnimatedColor>(new AnimatedColor());
		color->addColor(21, 104, 255, 255, 20);
		color->addColor(46, 219, 42, 255, 20);
		//color->addColor(249, 38, 88, 255, 20);
		graphics->setBackgroundColor(color);

		graphics->setColor(255, 255, 255, 255);

		return true;
	}

	void NoGame::unload()
	{
		graphics->pop();
	}

	void NoGame::update(float dt)
	{
		color->update(dt);
	}

	void NoGame::render()
	{
		float w = 256.0f;
		graphics->setFont(big);
		std::string s = "LOVE ";
		s += version_string();
		graphics->draw(s.c_str(), (float)graphics->getWidth()/2.0f - w/2.0f, (float)graphics->getHeight()/2.0f - 50.0f, w, LOVE_ALIGN_CENTER);
		graphics->setFont(small);
		graphics->draw("Now with More Mini Moose (tm).", (float)graphics->getWidth()/2.0f - w/2.0f, (float)graphics->getHeight()/2.0f - 20.0f, w, LOVE_ALIGN_CENTER);
	}

	void NoGame::keyPressed(int key)
	{
	}

} // love
