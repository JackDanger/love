/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_LABEL_H
#define LOVE_LABEL_H

// LOVE
#include "Image.h"
#include "Widget.h"

namespace love
{

	class Label : public Widget
	{
	private:
		pImage backgroundImage;
		
	public:

		/**
		* Default constructor.
		*
		* @param text The text for the label.
		**/
		Label(std::string text);
		
		/**
		* Deconstructor.
		**/
		virtual ~Label();
		
		/**
		* Sets the background image.
		*
		* @param image The background image.
		**/
		void setBackgroundImage(const pImage & image);
		
		/**
		* Gets the background image.
		**/
		pImage getBackgroundImage() const;

		// From Widget.
		void adjustWidth();
		void adjustHeight();
		void adjustContent();
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
