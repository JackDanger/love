#ifndef LOVE_BUTTON_H
#define LOVE_BUTTON_H

#include "AbstractColor.h"
#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

using std::string;

namespace love
{
	/**
	 * @class Button
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-15
	 * @brief A button to be used by the Menu.
	 **/
	class Button : public gcn::Button
	{
	private:
		int verticalAlignment;
		AbstractColor * color;
		AbstractColor * hoverColor;
		AbstractColor * pressedColor;
		AbstractColor * activeColor;
		AbstractColor * backgroundColor;
		AbstractColor * hoverBackgroundColor;
		AbstractColor * pressedBackgroundColor;
		AbstractColor * activeBackgroundColor;
		AbstractColor * borderColor;

	public:
		/**
		 * @param caption The caption of the button.
		 * @brief Constructor. Initializes the variables and aligns the caption to the middle of the button.
		 **/
		Button(const string caption);

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~Button();

		/**
		 * gcn::Button functions that should be documented:
		 * setCaption(caption);
		 * setSize(width, height);
		 * setWidth(width);
		 * setHeight(height);
		 * setBorderSize(size);
		 */

		/**
		 * @brief Adjusts the size of the button to the size of the caption.
		 **/
		void adjustSize();

		/**
		 * @param alignment The horizontal alignment (left, right, center).
		 * @brief Sets the horizontal alignment of the caption.
		 **/
		void align(int alignment);

		/**
		 * @param alignment The vertical alignment (left, right, center).
		 * @brief Sets the vertical alignment of the caption.
		 **/
		void valign(int alignment);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color.
		 **/
		void setColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the mouse is over the button.
		 **/
		void setHoverColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button is pressed.
		 **/
		void setPressedColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button has been pressed and is still active.
		 **/
		void setActiveColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets all the text colors.
		 **/
		void setAllColors(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		void setBackgroundColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the mouse is over the button.
		 **/
		void setHoverBackgroundColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button is pressed.
		 **/
		void setPressedBackgroundColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button has been pressed and is still active.
		 **/
		void setActiveBackgroundColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the all the background colors.
		 **/
		void setAllBackgroundColors(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		void setBorderColor(AbstractColor * color);

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color.
		 **/
		AbstractColor * getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the mouse is over the button.
		 **/
		AbstractColor * getHoverColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button is pressed.
		 **/
		AbstractColor * getPressedColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button has been pressed and is still active.
		 **/
		AbstractColor * getActiveColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color.
		 **/
		AbstractColor * getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the mouse is over the button.
		 **/
		AbstractColor * getHoverBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button is pressed.
		 **/
		AbstractColor * getPressedBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button has been pressed and is still active.
		 **/
		AbstractColor * getActiveBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the border color.
		 **/
		AbstractColor * getBorderColor();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the button background and text.
		 **/
		void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the button border.
		 **/
		void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<Button> pButton;
}

#endif