#include "console.h"

#include "love_opengl.h"
#include <SDL_opengl.h>

namespace love_opengl
{

	ConsoleElement::~ConsoleElement()
	{
		// Free memory.
		for(int i = 0;i<(int)children.size(); i++)
			delete children[i];
	}

	void ConsoleElement::add(ConsoleElement * e)
	{
		children.push_back(e);
	}

	bool ConsoleElement::outside(int y, Console * c) const
	{
		if(y < love_opengl::getHeight() - c->getHeight())
			return true;
		return false;
	}

	//
	// ConsoleString.
	//

	ConsoleString::ConsoleString(std::string str)
		: str(str)
	{
	}

	int ConsoleString::getHeight() const
	{
		return Console::LINE_HEIGHT;
	}

	bool ConsoleString::draw(int x, int y, int level, Console * c) const
	{
		if(outside(y, c))
			return false;

		// Assumes Font has been set.
		glColor4ub(255, 255, 255, 255);

		love_opengl::draw(str.c_str(), (float)x + ConsoleBox::PADDING, (float)y - 2);
		return true;
	}

	//
	// ConsoleRoot.
	//

	int ConsoleRoot::getHeight() const
	{
		int h = 0;
		for(int i = 0;i<(int)children.size();i++)
			h += children[i]->getHeight();
		return h;
	}

	bool ConsoleRoot::draw(int x, int y, int level, Console * c) const
	{
		int accumulated_height = 0;
		for(int i = (int)children.size()-1;i>=0;i--)
		{
			if(!children[i]->draw( x, y - accumulated_height, level+1, c))
				return false;
			accumulated_height += children[i]->getHeight();
		}
		return true;
	}

	//
	// ConsoleBox.
	//

	int ConsoleBox::getHeight() const
	{
		int h = 0;
		for(int i = 0;i<(int)children.size();i++)
			h += children[i]->getHeight();
		return h + 2*Console::LINE_HEIGHT;
	}

	bool ConsoleBox::draw(int x, int y, int level, Console * c) const
	{
		if(outside(y, c))
			return false;

		// Draw box.
		int height = getHeight();
		int w = c->getWidth();
		setColor();
		int pad = PADDING;
		quad(love::DRAW_FILL, 
			(float)(x+PADDING), (float)(y-pad), 
			(float)(w-x-PADDING), (float)(y-pad), 
			(float)(w-x-PADDING), (float)(y-height+pad), 
			(float)(x+PADDING), (float)(y-height+pad));

		// Draw children.
		int accumulated_height = 0;
		for(int i = (int)children.size()-1;i>=0;i--)
		{
			if(!children[i]->draw( x + PADDING*2, y - Console::LINE_HEIGHT - accumulated_height, level+1, c))
				return false;
			accumulated_height += children[i]->getHeight();
		}
		return true;
	}

	void ConsoleBox::setColor() const
	{
		love_opengl::setColor(255, 255, 255, 50);		
	}

	//
	// ConsoleError.
	//

	void ConsoleError::setColor() const
	{
		love_opengl::setColor(255, 0, 0, 100);				
	}

	//
	// ConsoleImage.
	//

	ConsoleImage::ConsoleImage(pImage image)
		: image(image)
	{
	}

	int ConsoleImage::getHeight() const
	{
		return (int)image->getHeight();
	}

	bool ConsoleImage::draw(int x, int y, int level, Console * c) const
	{
		if(outside(y, c))
			return false;

		setColor(255, 255, 255, 255);
		love_opengl::draw(image, (float)x, float(y));
		return true;
	}

	//
	// Console.
	//

	Console::Console(int width, int height)
		: width(width), height(height)
	{
		root = new ConsoleRoot();
		current_parent.push_back(root);
	}

	Console::~Console()
	{
		// Free memory.
		delete root;
	}

	int Console::getWidth() const
	{
		return width;
	}

	int Console::getHeight() const
	{
		return height;
	}

	void Console::push_error()
	{
		push(new ConsoleError());
	}

	void Console::push_box()
	{
		push(new ConsoleBox());
	}

	void Console::push(ConsoleElement * e)
	{
		// Add it.
		add(e);

		// Push onto current parent stack.
		current_parent.push_back(e);
	}

	void Console::pop()
	{
		if(current_parent.size() > 1)
			current_parent.pop_back();
	}

	void Console::add(const std::string & str)
	{
		add(new ConsoleString(str));
	}

	void Console::add(pImage image)
	{
		add(new ConsoleImage(image));
	}

	void Console::add(ConsoleElement * e)
	{
		current_parent.back()->children.push_back(e);
	}

	void Console::draw(int x, int y)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(x, 0, width, height);

		glPushMatrix();

		
		// Draw background.
		love_opengl::setColor(0, 0, 0, 100);
		quad(love::DRAW_FILL, 
			(float)(x), (float)(y), 
			(float)(width-x), (float)(y), 
			(float)(width-x), (float)(y-height), 
			(float)(x), (float)(y-height));

		root->draw(x, y - ConsoleBox::PADDING, 0, this);
		glPopMatrix();

		glDisable(GL_SCISSOR_TEST);
		
	}

}// love_opengl
