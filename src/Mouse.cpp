#include "Mouse.h"
#include "love.h"

namespace love
{

	Mouse::Mouse() : buttons(0), x(0), y(0)
	{
		setType(LOVE_TYPE_MOUSE);
	}

	Mouse::~Mouse()
	{
	}

	int Mouse::init()
	{
		return LOVE_OK;
	}

	int Mouse::getButtons() const
	{
		return buttons;
	}

	void Mouse::setButtons(int buttons)
	{
		this->buttons = buttons;
	}

	float Mouse::getX() const
	{
		return x;
	}

	void Mouse::setX(float x)
	{
		this->x = x;
	}

	float Mouse::getY() const
	{
		return y;
	}

	void Mouse::setY(float y)
	{
		this->y = y;
	}

	void Mouse::mousePressed(float x, float y, int state)
	{
		this->x = x;
		this->y = y;

		this->buttons |= state;
	}

	void Mouse::mouseReleased(float x, float y, int state)
	{
		this->x = x;
		this->y = y;
		this->buttons ^= state;
	}

	void Mouse::mouseMoved(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Mouse::setVisible(bool visible)
	{
		this->visible = visible;

		// In C++, this is horribly, ugly and pointless. 
		// However, it will be totally pretty in Lua. ^-^)'
		//if(visible)
		//	Core::hideMouse();
		//else
		//	Core::showMouse();
	}

	bool Mouse::isVisible() const
	{
		return visible;
	}

	bool Mouse::isDown(int button) const
	{
		return (this->buttons & button) != 0;
	}


}// love
