#ifndef LOVE_LABEL_H
#define LOVE_LABEL_H

#include "GUIElement.h"

namespace love
{
	/**
	 * @class Label
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-13
	 * @brief A label to be used by the Menu.
	 **/
	class Label : public gcn::Label, public GUIElement
	{
	protected:
		pAbstractImage backgroundImage;
		int verticalAlignment;

	public:
		/**
		 * @param caption The label's caption.
		 * @brief Constructor. Initializes the variables and aligns the caption to the middle of the label.
		 **/
		Label(const string & caption = "");

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~Label();

		/**
		 * @param width The new width.
		 * @param height The new height.
		 * @brief Sets the size of the Label.
		 **/
		virtual void setSize(int width, int height);

		/**
		 * @param width The new width.
		 * @brief Sets the width of the Label.
		 **/
		virtual void setWidth(int width);

		/**
		 * @param height The new height.
		 * @brief Sets the height of the Label.
		 **/
		virtual void setHeight(int height);

		/**
		 * @param size The new border size.
		 * @brief Sets the size of the Label's border.
		 **/
		virtual void setBorderSize(unsigned int size);

		/**
		 * @param caption The text in the label.
		 * @brief Sets the caption of the label.
		 **/
		virtual void setCaption(const string & caption);

		/**
		 * @param color An AbstractColor.
		 * @brief Sets the current background color.
		 **/
		virtual void setBackgroundColor(const pAbstractColor & color);

		/**
		 * @param font An AbstractFont.
		 * @brief Sets the current font.
		 **/
		virtual void setFont(const pAbstractFont & font);

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
		 * @param color An AbstractImage object.
		 * @brief Sets the background.
		 **/
		virtual void setBackgroundImage(const pAbstractImage & image);

		/**
		 * @return The width of the Label.
		 * @brief Returns the width of the Label.
		 **/
		virtual int getWidth();

		/**
		 * @return The width of the Label.
		 * @brief Returns the width of the Label.
		 **/
		virtual int getHeight();

		/**
		 * @return The border size.
		 * @brief Returns the size of the border.
		 **/
		virtual unsigned int getBorderSize();

		/**
		 * @return The current caption.
		 * @brief Returns the Label's caption.
		 **/
		virtual const string & getCaption();

		/**
		 * @return An AbstractColor.
		 * @brief Gets the current background color.
		 **/
		virtual pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractImage.
		 * @brief Gets the current background.
		 **/
		virtual pAbstractImage getBackgroundImage();

		/**
		 * @return An AbstractFont.
		 * @brief Gets the current font.
		 **/
		virtual pAbstractFont getFont();

		/**
		 * @brief Adjusts the size of the label according to the size of the caption.
		 **/
		virtual void adjustSize();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the label background and text.
		 **/
		virtual void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the label border.
		 **/
		virtual void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<Label> pLabel;
}

#endif

