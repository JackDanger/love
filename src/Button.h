/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_BUTTON_H
#define LOVE_BUTTON_H

// LOVE
#include "Widget.h"
#include "Image.h"

namespace love
{

	class Button : public Widget
	{
	private:
		//std::string text;
		pImage up, down, hover;
		int state;
		//float width, height;
	public:

		Button(std::string text, pImage up, pImage down, pImage hover);
		virtual ~Button();

		// From Widget
		void update(float dt);
		void render() const;
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);
		void mouseMoved(float x, float y);
		void keyPressed(int key);
		void keyReleased(int key);

	};

	typedef boost::shared_ptr<Button> pButton;

} // love

#endif // LOVE_BUTTON_H
