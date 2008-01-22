#include "Button.h"
#include "using_graphics.h"
#include "using_mouse.h"

namespace love
{

	Button::Button(std::string text, pImage up, pImage down, pImage hover) 
		: Widget(true, false), text(text), state(0), up(up), down(down), hover(hover)
	{
		width = 79;
		height = 21;
	}

	Button::~Button()
	{
	}

	void Button::update(float dt)
	{
		float x = love::mouse->getX();
		float y = love::mouse->getY();

		if(x >= this->x && x <= this->x + width && 
			y >= this->y && y <= this->y + height)
		{
			if(love::mouse->isDown(LOVE_MOUSE_LEFT))
				this->state = 1;
			else
				this->state = 2;
		}
		else
			this->state = 0;
	}

	void Button::render() const
	{
		if(this->state == 0 && up != 0)
			up->render(x, y);
		else if(this->state == 1 && down != 0)
			down->render(x, y);
		else if(this->state == 2 && hover != 0)
			hover->render(x, y);

		// Render text.
		graphics->draw(text.c_str(), x + 7, y + 14);
	}

	void Button::mousePressed(float x, float y, int button)
	{
		if(x >= this->x && x <= this->x + width && 
			y >= this->y && y <= this->y + height)
		{
			printf("ButtonEvent\n");
		}
	}

	void Button::mouseReleased(float x, float y, int button)
	{
		this->state = 0;
	}

	void Button::mouseMoved(float x, float y)
	{
	}

	void Button::keyPressed(int key)
	{
	}

	void Button::keyReleased(int key)
	{
	}

}