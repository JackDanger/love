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
		pAbstractColor color;
		pAbstractColor hoverColor;
		pAbstractColor pressedColor;
		pAbstractColor activeColor;
		pAbstractColor backgroundColor;
		pAbstractColor hoverBackgroundColor;
		pAbstractColor pressedBackgroundColor;
		pAbstractColor activeBackgroundColor;
		pAbstractColor borderColor;

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
		 * setSize(width, height);
		 * setWidth(width);
		 * setHeight(height);
		 * setBorderSize(size);
		 */

		/**
		 * @param caption The text in the button.
		 * @brief Sets the caption of the button.
		 **/
		virtual void setCaption(const char * caption);

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
		void setColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the mouse is over the button.
		 **/
		void setHoverColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button is pressed.
		 **/
		void setPressedColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button has been pressed and is still active.
		 **/
		void setActiveColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets all the text colors.
		 **/
		void setAllColors(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		void setBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the mouse is over the button.
		 **/
		void setHoverBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button is pressed.
		 **/
		void setPressedBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button has been pressed and is still active.
		 **/
		void setActiveBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the all the background colors.
		 **/
		void setAllBackgroundColors(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		void setBorderColor(const pAbstractColor * color);

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color.
		 **/
		pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the mouse is over the button.
		 **/
		pAbstractColor getHoverColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button is pressed.
		 **/
		pAbstractColor getPressedColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button has been pressed and is still active.
		 **/
		pAbstractColor getActiveColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color.
		 **/
		pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the mouse is over the button.
		 **/
		pAbstractColor getHoverBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button is pressed.
		 **/
		pAbstractColor getPressedBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button has been pressed and is still active.
		 **/
		pAbstractColor getActiveBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the border color.
		 **/
		pAbstractColor getBorderColor();

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

