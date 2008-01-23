#include "Widget.h"

namespace love
{

	std::list<Widget *> Widget::keylisteners;
	std::list<Widget *> Widget::mouselisteners;

	Widget::Widget() : mouse(false), keyboard(false), paddingTop(0), paddingBottom(0), paddingLeft(0), paddingRight(0), align(love::LOVE_ALIGN_CENTER), valign(love::LOVE_ALIGN_CENTER), innerx(0), innery(0)
	{
	}

	Widget::Widget(bool mouse, bool keyboard) : mouse(mouse), keyboard(keyboard), paddingTop(0), paddingBottom(0), paddingLeft(0), paddingRight(0), align(love::LOVE_ALIGN_CENTER), valign(love::LOVE_ALIGN_CENTER), innerx(0), innery(0)
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
		
		adjustContent();
	}
	
	void Widget::setX(float x)
	{
		this->x = x;
		
		adjustContent();
	}
	
	void Widget::setY(float y)
	{
		this->y = y;
		
		adjustContent();
	}
	
	float Widget::getX() const
	{
		return x;
	}
	
	float Widget::getY() const
	{
		return y;
	}
	
	void Widget::setSize(float width, float height)
	{
		this->width = width;
		this->height = height;
		
		adjustContent();
	}

	void Widget::setWidth(float width)
	{
		this->width = width;
		
		adjustContent();
	}
	
	void Widget::setHeight(float height)
	{
		this->height = height;
		
		adjustContent();
	}
	
	float Widget::getWidth() const
	{
		return width;
	}
	
	float Widget::getHeight() const
	{
		return height;
	}
		
	void Widget::adjustSize()
	{
	}
	
	void Widget::adjustContent()
	{
		innerx = x;
		innery = y;
	}
	
	void Widget::setFont(const pFont & font)
	{
		this->font = font;
		
		adjustContent();
	}
	
	void Widget::setColor(const pColor & color)
	{
		this->color = color;
	}
	
	void Widget::setBackgroundColor(const pColor & color)
	{
		this->backgroundColor = color;
	}
	
	pFont Widget::getFont() const
	{
		return font;
	}
	
	pColor Widget::getColor() const
	{
		return color;
	}
	
	pColor Widget::getBackgroundColor() const
	{
		return backgroundColor;
	}
	
	void Widget::setText(const std::string & text)
	{
		this->text = text;
		
		adjustContent();
	}
	
	std::string Widget::getText() const
	{
		return text;
	}
	
	void Widget::setAlignment(int alignment)
	{
		if(alignment != love::LOVE_ALIGN_LEFT && alignment != love::LOVE_ALIGN_RIGHT && alignment != love::LOVE_ALIGN_CENTER)
			this->align = love::LOVE_ALIGN_CENTER;
		else
			this->align = alignment;
		
		adjustContent();
	}
	
	int Widget::getAlignment() const
	{
		return align;
	}
	
	void Widget::setVerticalAlignment(int alignment)
	{
		if(alignment != love::LOVE_ALIGN_TOP && alignment != love::LOVE_ALIGN_BOTTOM && alignment != love::LOVE_ALIGN_CENTER)
			this->valign = love::LOVE_ALIGN_CENTER;
		else
			this->valign = alignment;
		
		adjustContent();
	}
	
	int Widget::getVerticalAlignment() const
	{
		return valign;
	}
	
	void Widget::setPadding(int padding)
	{
		this->paddingTop = padding;
		this->paddingRight = padding;
		this->paddingBottom = padding;
		this->paddingLeft = padding;
		
		adjustContent();
	}
	
	void Widget::setPadding(int top, int right, int bottom, int left)
	{
		this->paddingTop = top;
		this->paddingRight = right;
		this->paddingBottom = bottom;
		this->paddingLeft = left;
		
		adjustContent();
	}
	
	void Widget::setTopPadding(int top)
	{
		this->paddingTop = top;
		
		adjustContent();
	}
	
	void Widget::setBottomPadding(int bottom)
	{
		this->paddingBottom = bottom;
		
		adjustContent();
	}
	
	void Widget::setLeftPadding(int left)
	{
		this->paddingLeft = left;
		
		adjustContent();
	}
	
	void Widget::setRightPadding(int right)
	{
		this->paddingRight = right;
		
		adjustContent();
	}
	
	int Widget::getTopPadding() const
	{
		return paddingTop;
	}
	
	int Widget::getBottomPadding() const
	{
		return paddingBottom;
	}
	
	int Widget::getLeftPadding() const
	{
		return paddingLeft;
	}
	
	int Widget::getRightPadding() const
	{
		return paddingRight;
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
