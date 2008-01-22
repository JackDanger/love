#include "Label.h"
#include "using_graphics.h"

namespace love
{

	Label::Label(std::string text) : Widget(false, false), text(text)
	{
	}

	Label::~Label()
	{
	}


	void Label::update(float dt)
	{
	}

	void Label::render() const
	{
		graphics->draw(text.c_str(), x, y);
	}

	void Label::mousePressed(float x, float y, int button)
	{
	}

	void Label::mouseReleased(float x, float y, int button)
	{
	}

	void Label::mouseMoved(float x, float y)
	{
	}

	void Label::keyPressed(int key)
	{
	}

	void Label::keyReleased(int key)
	{
	}

}