#ifndef LOVE_TEXT_FIELD_H
#define LOVE_TEXT_FIELD_H

#include "AbstractColor.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	/**
	 * @class TextField
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-08-16
	 * @brief A text field to be used by the Menu.
	 **/
	class TextField : public gcn::TextField
	{
	private:
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pAbstractColor activeColor;
		pAbstractColor activeBackgroundColor;

	public:
		/**
		 * @param text Text which is to be in the TextField.
		 * @brief Constructor. Initiates the variables.
		 **/
		TextField(const char * text = "");

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~TextField();

		/**
		 * gcn::TextField functions that should be documented:
		 * adjustSize()
		 * setSize(width, height)
		 * setWidth(width)
		 * setHeight(height)
		 * setBorderSize(size)
		 * setText(text)
		 * getText()
		 */

		/**
		 * @param text The text in the text field.
		 * @brief Sets the text of the text field.
		 **/
		virtual void setText(const char * text);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color.
		 **/
		void setColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the text field is active.
		 **/
		void setActiveColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		void setBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the text field is active.
		 **/
		void setActiveBackgroundColor(const pAbstractColor * color);

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
		 * @brief Returns the background color.
		 **/
		pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the text label is active.
		 **/
		pAbstractColor getActiveColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the text label is active.
		 **/
		pAbstractColor getActiveBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the border color.
		 **/
		pAbstractColor getBorderColor();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the text field background and text.
		 **/
		void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the text field border.
		 **/
		void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<TextField> pTextField;
}

#endif

