/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_WIDGET_H
#define LOVE_WIDGET_H

// Boost
#include <boost/shared_ptr.hpp>

// STD
#include <list>

namespace love
{
	/**
	* @author Michael Enger
	* @date 2008-01-22
	**/
	class Widget
	{
	private:
		std::list<boost::shared_ptr<Widget> > children;
		static std::list<Widget *> keylisteners;
		static std::list<Widget *> mouselisteners;
		bool mouse, keyboard;

	protected:
		float x, y;
	public:

		Widget();
		Widget(bool mouse, bool keyboard);
		virtual ~Widget();

		void setPosition(float x, float y);
		void updateChildren(float dt);
		void renderChildren() const;


		virtual void update(float dt);
		virtual void render() const;
		virtual void mousePressed(float x, float y, int button);
		virtual void mouseReleased(float x, float y, int button);
		virtual void mouseMoved(float x, float y);
		virtual void keyPressed(int key);
		virtual void keyReleased(int key);

		static void distributeMousePressed(float x, float y, int button);
		static void distributeMouseReleased(float x, float y, int button);
		static void distributeMouseMoved(float x, float y);
		static void distributeKeyPressed(int key);
		static void distributeKeyReleased(int key);

	};

	typedef boost::shared_ptr<Widget> pWidget;

} // love

#endif // LOVE_WIDGET_H

