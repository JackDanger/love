/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_LABEL_H
#define LOVE_LABEL_H

// LOVE
#include "Widget.h"

namespace love
{

	class Label : public Widget
	{
	private:
		std::string text;
	public:

		Label(std::string text);
		virtual ~Label();

		void update(float dt);
		void render() const;
		void mousePressed(float x, float y, int button);
		void mouseReleased(float x, float y, int button);
		void mouseMoved(float x, float y);
		void keyPressed(int key);
		void keyReleased(int key);

	};

	typedef boost::shared_ptr<Label> pLabel;

} // love

#endif // LOVE_LABEL_H

