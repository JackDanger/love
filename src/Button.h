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
	protected:
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
		 * @param width The new width.
		 * @param height The new height.
		 * @brief Sets the size of the Button.
		 **/
		virtual void setSize(int width, int height);

		/**
		 * @param width The new width.
		 * @brief Sets the width of the Button.
		 **/
		virtual void setWidth(int width);

		/**
		 * @param height The new height.
		 * @brief Sets the height of the Button.
		 **/
		virtual void setHeight(int height);

		/**
		 * @param size The new border size.
		 * @brief Sets the size of the Button's border.
		 **/
		virtual void setBorderSize(unsigned int size);

		/**
		 * @param caption The text in the button.
		 * @brief Sets the caption of the button.
		 **/
		virtual void setCaption(const char * caption);

		/**
		 * @param alignment The horizontal alignment (left, right, center).
		 * @brief Sets the horizontal alignment of the caption.
		 **/
		virtual void align(int alignment);

		/**
		 * @param alignment The vertical alignment (left, right, center).
		 * @brief Sets the vertical alignment of the caption.
		 **/
		virtual void valign(int alignment);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color.
		 **/
		virtual void setColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the mouse is over the button.
		 **/
		virtual void setHoverColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button is pressed.
		 **/
		virtual void setPressedColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button has been pressed and is still active.
		 **/
		virtual void setActiveColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets all the text colors.
		 **/
		virtual void setAllColors(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		virtual void setBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the mouse is over the button.
		 **/
		virtual void setHoverBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button is pressed.
		 **/
		virtual void setPressedBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button has been pressed and is still active.
		 **/
		virtual void setActiveBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the all the background colors.
		 **/
		virtual void setAllBackgroundColors(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		virtual void setBorderColor(const pAbstractColor * color);

		/**
		 * @return The width of the Button.
		 * @brief Returns the width of the button.
		 **/
		virtual int getWidth();

		/**
		 * @return The height of the Button.
		 * @brief Returns the height of the button.
		 **/
		virtual int getHeight();

		/**
		 * @return The size of the Button's border.
		 * @brief Returns the size of the button's border.
		 **/
		virtual unsigned int getBorderSize();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color.
		 **/
		virtual pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the mouse is over the button.
		 **/
		virtual pAbstractColor getHoverColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button is pressed.
		 **/
		virtual pAbstractColor getPressedColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the button has been pressed and is still active.
		 **/
		virtual pAbstractColor getActiveColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color.
		 **/
		virtual pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the mouse is over the button.
		 **/
		virtual pAbstractColor getHoverBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button is pressed.
		 **/
		virtual pAbstractColor getPressedBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the button has been pressed and is still active.
		 **/
		virtual pAbstractColor getActiveBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the border color.
		 **/
		virtual pAbstractColor getBorderColor();

		/**
		 * @brief Adjusts the size of the button to the size of the caption.
		 **/
		virtual void adjustSize();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the button background and text.
		 **/
		virtual void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the button border.
		 **/
		virtual void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<Button> pButton;
}

#endif

