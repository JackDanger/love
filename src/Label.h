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
	private:
		AbstractColor * color;
		AbstractColor * backgroundColor;
		AbstractColor * borderColor;
		AbstractImage * background;
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
		 * setCaption(caption)
		 * setSize(width, height)
		 * setWidth(width)
		 * setHeight(height)
		 * setBorderSize(size)
		 */

		/**
		 * @brief Adjusts the size of the label according to the size of the caption.
		 **/
		void adjustSize();

		/**
		 * @param alignment The horizontal alignment (left, right, center).
		 * @brief Sets the horizontal alignment of the caption.
		 **/
		void align(int alignment);

		/**
		 * @param alignment The vertical alignment (top, bottom, center).
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
		 * @brief Sets the background color.
		 **/
		void setBackgroundColor(AbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		void setBorderColor(AbstractColor * color);

		void setBackground(AbstractImage * image);

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the text color.
		 **/
		AbstractColor * getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the background color.
		 **/
		AbstractColor * getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Gets the border color.
		 **/
		AbstractColor * getBorderColor();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the label background and text.
		 **/
		void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the label border.
		 **/
		void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<Label> pLabel;
}

#endif

