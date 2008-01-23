/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_WIDGET_H
#define LOVE_WIDGET_H

// LOVE
#include "Color.h"
#include "Font.h"
#include "love_align.h"

// Boost
#include <boost/shared_ptr.hpp>

// STD
#include <list>
#include <string>

namespace love
{
	/**
	* @author Michael Enger (LIES!)
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
		float x, y, width, height;
		int paddingTop, paddingBottom, paddingLeft, paddingRight;
		int align, valign;
		
		// The internal position of the content (based on padding and alignment)
		float innerx, innery;
		
		// Custom font and colors
		pFont font;
		pColor color;
		pColor backgroundColor;
		
		// All widgets have a text aspect
		std::string text;
		
	public:

		/**
		* Default constructor.
		**/
		Widget();
		
		/**
		* Constructor which determines if the created widget is a mouse/keyboard listener and adds it where relevant.
		*
		* @param mouse Whether the widget is a mouse listener.
		* @param keyboard Whether the widget is a keyboard listener.
		**/
		Widget(bool mouse, bool keyboard);
		
		/**
		* Deconstructor which removes the widget from the list where relevant.
		**/
		virtual ~Widget();

		/**
		* Sets the position of the widget.
		*
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		void setPosition(float x, float y);
		
		/**
		* Sets the x-coordinate of the widget.
		*
		* @param x The x-coordinate.
		**/
		void setX(float x);
		
		/**
		 * Sets the y-coordinate of the widget.
		 *
		 * @param y The y-coordinate.
		 **/
		void setY(float y);
		
		/**
		* Returns the x-coordinate.
		**/
		float getX() const;
		
		/**
		* Returns the y-coordinate.
		**/
		float getY() const;
		
		/**
		* Sets the size of the widget.
		*
		* @param width The width of the widget.
		* @param height The height of the widget.
		**/
		void setSize(float width, float height);
		
		/**
		* Sets the width of the widget.
		*
		* @param width The width of the widget.
		**/
		void setWidth(float width);
		
		/**
		* Sets the height of the widget.
		*
		* @param height THe height of the widget.
		**/
		void setHeight(float height);
		
		/**
		* Returns the width of the widget.
		**/
		float getWidth() const;
		
		/**
		* Returns the height of the widget.
		**/
		float getHeight() const;
		
		/**
		* Automatically adjusts the size of the widget in respect to the contents.
		**/
		virtual void adjustSize();
		
		/**
		* Automatically adjusts the content of the widget in respect to the size, padding and alignment.
		* (this is called whenver anything is changed, rather than doing the calculations during render)
		**/
		virtual void adjustContent();
		
		/**
		* Sets a custom font for the widget.
		*
		* @param font The font.
		**/
		void setFont(const pFont & font);
		
		/**
		* Sets a custom color for the widget contents.
		*
		* @param color The color.
		**/
		void setColor(const pColor & color);
		
		/**
		 * Sets a custom background color for the widget contents.
		 *
		 * @param color The color.
		 **/
		void setBackgroundColor(const pColor & color);
		
		/**
		* Returns the custom font of the widget.
		**/
		pFont getFont() const;
		
		/**
		* Returns the custom color of the widget.
		**/
		pColor getColor() const;
		
		/**
		* Returns the custom background color of the widget.
		**/
		pColor getBackgroundColor() const;
		
		/**
		* Sets the text of the widget.
		*
		* @param text The text.
		**/
		void setText(const std::string & text);
		
		/**
		* Gets the text of the widget.
		**/
		std::string getText() const;
		
		/**
		* Sets the horizontal alignment of the widget.
		*
		* @param alignment The alignment (left, right or center).
		**/
		void setAlignment(int alignment);
		
		/**
		* Gets the horizontal alignment of the widget.
		**/
		int getAlignment() const;
		
		/**
		* Sets the vertical alignment of the widget.
		*
		* @param alignment The alignment (top, bottom or center).
		**/
		void setVerticalAlignment(int alignment);
		
		/**
		* Gets the vertical alignment of the widget.
		**/
		int getVerticalAlignment() const;
		
		/**
		* Sets the padding of every side of the widget.
		*
		* @param padding The padding.
		**/
		void setPadding(int padding);
		
		/**
		* Sets the padding of every side of the widget.
		*
		* @param top The top padding.
		* @param right The right padding.
		* @param bottom The bottom padding.
		* @param left The left padding.
		**/
		void setPadding(int top, int right, int bottom, int left);
		
		/**
		* Sets the top padding of the widget.
		*
		* @param top The top padding.
		**/
		void setTopPadding(int top);
		
		/**
		* Sets the bottom padding of the widget.
		*
		* @param bottom The bottom padding.
		**/
		void setBottomPadding(int bottom);
		
		/**
		* Sets the left padding of the widget.
		*
		* @param left The left padding.
		**/
		void setLeftPadding(int left);
		
		/**
		* Sets the right padding of the widget.
		*
		* @param right The right padding.
		**/
		void setRightPadding(int right);
		
		/**
		* Gets the top padding.
		**/
		int getTopPadding() const;
		
		/**
		* Gets the bottom padding.
		**/
		int getBottomPadding() const;
		
		/**
		* Gets the left padding.
		**/
		int getLeftPadding() const;
		
		/**
		* Gets the right padding.
		**/
		int getRightPadding() const;
		
		/**
		* Updates all the children of this widget.
		*
		* @param dt Seconds since the last time this function was called.
		**/
		void updateChildren(float dt);
		
		/**
		* Renders all the children of this widget.
		**/
		void renderChildren() const;

		/**
		* Updates this widget.
		*
		* @param dt Seconds since the last time this function was called.
		**/
		virtual void update(float dt);
		
		/**
		* Renders this widget.
		**/
		virtual void render() const;
		
		/**
		* Called when a mouse button is pressed.
		*
		* @param x The x-coordinate where the mouse button was pressed.
		* @param y The y-coordinate where the mouse button was pressed.
		* @param button The mouse button which was pressed.
		**/
		virtual void mousePressed(float x, float y, int button);
		
		/**
		* Called when a mouse button is released.
		*
		* @param x The x-coordinate where the mouse button was released.
		* @param y The y-coordinate where the mouse button was released.
		* @param button The mouse button which was released.
		**/
		virtual void mouseReleased(float x, float y, int button);
		
		/**
		* Called when the mouse is moved within the widget.
		*
		* @param x The x-coordinate of the mouse pointer.
		* @param y The y-coordinate of the mouse pointer.
		**/
		virtual void mouseMoved(float x, float y);
		
		/**
		* Called when a key is pressed.
		*
		* @param key The key which was pressed.
		**/
		virtual void keyPressed(int key);
		
		/**
		* Called when a key was released.
		*
		* @param key The key which was released.
		**/
		virtual void keyReleased(int key);

		/**
		* Distributes the mouse pressed event to all mouse listeners.
		* (calls the respective widget's mousePressed() functions)
		**/
		static void distributeMousePressed(float x, float y, int button);
		
		/**
		 * Distributes the mouse released event to all mouse listeners.
		 * (calls the respective widget's mouseReleased() functions)
		 **/
		static void distributeMouseReleased(float x, float y, int button);
		
		/**
		 * Distributes the mouse moved event to all mouse listeners.
		 * (calls the respective widget's mouseMoved() functions)
		 **/
		static void distributeMouseMoved(float x, float y);
		
		/**
		 * Distributes the key pressed event to all mouse listeners.
		 * (calls the respective widget's keyPressed() functions)
		 **/
		static void distributeKeyPressed(int key);
		
		/**
		 * Distributes the key released event to all mouse listeners.
		 * (calls the respective widget's keyReleased() functions)
		 **/
		static void distributeKeyReleased(int key);

	};

	typedef boost::shared_ptr<Widget> pWidget;

} // love

#endif // LOVE_WIDGET_H

