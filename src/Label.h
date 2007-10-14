#ifndef LOVE_LABEL_H
#define LOVE_LABEL_H

#include "AbstractColor.h"
#include "AbstractImage.h"
#include "Font.h"
#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

using std::string;

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
	class Label : public gcn::Label
	{
	protected:
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pAbstractImage background;
		int verticalAlignment;

	public:
		/**
		 * @param caption The label's caption.
		 * @brief Constructor. Initializes the variables and aligns the caption to the middle of the label.
		 **/
		Label(const string caption = "");

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~Label();

		/**
		 * gcn::Label functions that should be documented:
		 * setSize(width, height)
		 * setWidth(width)
		 * setHeight(height)
		 * setBorderSize(size)
		 */

		/**
		 * @param caption The text in the label.
		 * @brief Sets the caption of the label.
		 **/
		virtual void setCaption(const char * caption);

		/**
		 * @brief Adjusts the size of the label according to the size of the caption.
		 **/
		virtual void adjustSize();

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
		 * @param color An AbstractColor object.
		 * @brief Sets the text color.
		 **/
		virtual void setColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		virtual void setBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		virtual void setBorderColor(const pAbstractColor * color);

		virtual void setBackground(const pAbstractImage * image);

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the text color.
		 **/
		virtual pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the background color.
		 **/
		virtual pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the border color.
		 **/
		virtual pAbstractColor getBorderColor();

		/**
		 * @return An AbstractImage object.
		 * @brief Gets the background image.
		 **/
		virtual pAbstractImage getBackground();

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

