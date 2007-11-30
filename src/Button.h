#ifndef LOVE_BUTTON_H
#define LOVE_BUTTON_H

#include "GUIElement.h"

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
	class Button : public gcn::Button, public GUIElement
	{
	protected:
		int verticalAlignment;
		pAbstractColor hoverColor;
		pAbstractColor pressedColor;
		pAbstractColor hoverBackgroundColor;
		pAbstractColor pressedBackgroundColor;

		pAbstractImage defaultImage;
		pAbstractImage hoverImage;
		pAbstractImage pressedImage;

	public:
		/**
		 * @param caption The caption of the button.
		 * @brief Constructor. Initializes the variables and aligns the caption to the middle of the button.
		 **/
		Button(const string & caption);

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
		virtual void setCaption(const string & caption);

		/**
		 * @param name The new name.
		 * @brief Sets the name of the button (for event handling).
		 **/
		virtual void setName(const string & name);

		/**
		 * @param alignment The horizontal alignment (left, right, center).
		 * @brief Sets the horizontal alignment of the caption.
		 **/
		virtual void align(int alignment);

		/**
		 * @param alignment The vertical alignment (top, bottom, center).
		 * @brief Sets the vertical alignment of the caption.
		 **/
		virtual void valign(int alignment);

		/**
		 * @param color An AbstractColor.
		 * @brief Sets the current background color.
		 **/
		virtual void setBackgroundColor(const pAbstractColor & color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the mouse is over the button.
		 **/
		virtual void setHoverColor(const pAbstractColor & color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the button is pressed.
		 **/
		virtual void setPressedColor(const pAbstractColor & color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the mouse is over the button.
		 **/
		virtual void setHoverBackgroundColor(const pAbstractColor & color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the button is pressed.
		 **/
		virtual void setPressedBackgroundColor(const pAbstractColor & color);

		/**
		 * @param image An AbstractImage object.
		 * @brief Sets the default image.
		 **/
		virtual void setDefaultImage(const pAbstractImage & image);

		/**
		 * @param image An AbstractImage object.
		 * @brief Sets the image when the mouse is hovering over the button.
		 **/
		virtual void setHoverImage(const pAbstractImage & image);

		/**
		 * @param image An AbstractImage object.
		 * @brief Sets the image when the button is pressed.
		 **/
		virtual void setPressedImage(const pAbstractImage & image);

		/**
		 * @param font An AbstractFont.
		 * @brief Sets the current font.
		 **/
		virtual void setFont(const pAbstractFont & font);

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
		 * @return The caption in the button.
		 * @brief Returns the button's caption.
		 **/
		virtual const string & getCaption();

		/**
		 * @return The button's name.
		 * @brief Returns the button's name.
		 **/
		virtual const string & getName();

		/**
		 * @return An AbstractColor.
		 * @brief Gets the current background color.
		 **/
		virtual pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor.
		 * @brief Returns the color of the text in the button when the mouse hovers over it.
		 **/
		virtual pAbstractColor getHoverColor();

		/**
		 * @return An AbstractColor.
		 * @brief Returns the color of the text in the button when the mouse hovers over it.
		 **/
		virtual pAbstractColor getPressedColor();

		/**
		 * @return An AbstractColor.
		 * @brief Returns the color of the text in the button when the mouse hovers over it.
		 **/
		virtual pAbstractColor getHoverBackgroundColor();

		/**
		 * @return An AbstractColor.
		 * @brief Returns the color of the text in the button when the mouse hovers over it.
		 **/
		virtual pAbstractColor getPressedBackgroundColor();

		/**
		 * @return An AbstractImage.
		 * @brief Returns the default image.
		 **/
		virtual pAbstractImage getDefaultImage();

		/**
		 * @return An AbstractImage.
		 * @brief Returns the hover image.
		 **/
		virtual pAbstractImage getHoverImage();

		/**
		 * @return An AbstractImage.
		 * @brief Returns the pressed image.
		 **/
		virtual pAbstractImage getPressedImage();

		/**
		 * @return An AbstractFont.
		 * @brief Gets the current font.
		 **/
		virtual pAbstractFont getFont();

		/**
		 * @brief Adjusts the size of the button to the size of the caption.
		 **/
		virtual void adjustSize();

		/**
		 * @return False. Always.
		 * @brief Used to circumvent the ugly GUIchan focused graphics.
		 **/
		virtual bool isFocused() const;

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

