#include "Widget.h"

namespace love
{

	std::list<Widget *> Widget::keylisteners;
	std::list<Widget *> Widget::mouselisteners;

	Widget::Widget() : mouse(false), keyboard(false)
	{
	}

	Widget::Widget(bool mouse, bool keyboard) : mouse(mouse), keyboard(keyboard)
	{
		if(mouse)
			Widget::mouselisteners.push_back(this);
		if(keyboard)
			Widget::keylisteners.push_back(this);
	}

	Widget::~Widget()
	{
		if(mouse)
			Widget::mouselisteners.remove(this);
		if(keyboard)
			Widget::keylisteners.remove(this);
	}

	void Widget::setPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Widget::updateChildren(float dt)
	{
		std::list<boost::shared_ptr<Widget> >::iterator i = children.begin();

		while(i != children.end())
		{
			(*i)->update(dt);
			i++;
		}
	}

	void Widget::renderChildren() const
	{
		std::list<boost::shared_ptr<Widget> >::const_iterator i = children.begin();

		while(i != children.end())
		{
			(*i)->render();
			i++;
		}
	}


	void Widget::update(float dt)
	{
		updateChildren(dt);
	}

	void Widget::render() const
	{
		renderChildren();
	}

	void Widget::mousePressed(float x, float y, int button)
	{
	}

	void Widget::mouseReleased(float x, float y, int button)
	{
	}

	void Widget::mouseMoved(float x, float y)
	{
	}

	void Widget::keyPressed(int key)
	{
	}

	void Widget::keyReleased(int key)
	{
	}

	/**
	* STATIC
	**/

	void Widget::distributeMousePressed(float x, float y, int button)
	{	

		for(std::list<Widget *>::iterator i = Widget::mouselisteners.begin();
			i != Widget::mouselisteners.end();
			i++)
		{
			(*i)->mousePressed(x, y, button);
		}
	}

	void Widget::distributeMouseReleased(float x, float y, int button)
	{
		for(std::list<Widget *>::iterator i = Widget::mouselisteners.begin();
			i != Widget::mouselisteners.end();
			i++)
		{
			(*i)->mouseReleased(x, y, button);
		}
	}

	void Widget::distributeMouseMoved(float x, float y)
	{
		for(std::list<Widget *>::iterator i = Widget::mouselisteners.begin();
			i != Widget::mouselisteners.end();
			i++)
		{
			(*i)->mouseMoved(x, y);
		}
	}

	void Widget::distributeKeyPressed(int key)
	{
		for(std::list<Widget *>::iterator i = Widget::mouselisteners.begin();
			i != Widget::mouselisteners.end();
			i++)
		{
			(*i)->keyPressed(key);
		}
	}

	void Widget::distributeKeyReleased(int key)
	{
		for(std::list<Widget *>::iterator i = Widget::mouselisteners.begin();
			i != Widget::mouselisteners.end();
			i++)
		{
			(*i)->keyReleased(key);
		}
	}


}