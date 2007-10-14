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
	protected:
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
		 * @param width The new width.
		 * @param height The new height.
		 * @brief Sets the size of the TextField.
		 **/
		virtual void setSize(int width, int height);

		/**
		 * @param width The new width.
		 * @brief Sets the width of the TextField.
		 **/
		virtual void setWidth(int width);

		/**
		 * @param height The new height.
		 * @brief Sets the height of the TextField.
		 **/
		virtual void setHeight(int height);

		/**
		 * @param size The new border size.
		 * @brief Sets the size of the TextField's border.
		 **/
		virtual void setBorderSize(unsigned int size);

		/**
		 * @param text The text in the text field.
		 * @brief Sets the text of the text field.
		 **/
		virtual void setText(const char * text);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color.
		 **/
		virtual void setColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the text color when the text field is active.
		 **/
		virtual void setActiveColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color.
		 **/
		virtual void setBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the background color when the text field is active.
		 **/
		virtual void setActiveBackgroundColor(const pAbstractColor * color);

		/**
		 * @param color An AbstractColor object.
		 * @brief Sets the border color.
		 **/
		virtual void setBorderColor(const pAbstractColor * color);

		/**
		 * @return The width of the TextField.
		 * @brief Returns the width of the TextField.
		 **/
		virtual int getWidth();

		/**
		 * @return The height of the TextField.
		 * @brief Returns the height of the TextField.
		 **/
		virtual int getHeight();

		/**
		 * @return The size of the TextField's border.
		 * @brief Returns the size of the TextField's border.
		 **/
		virtual unsigned int getBorderSize();

		/**
		 * @return The text in the TextField.
		 * @brief Returns the text in the TextField.
		 **/
		virtual const char * getText();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color.
		 **/
		virtual pAbstractColor getColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color.
		 **/
		virtual pAbstractColor getBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the text color when the text label is active.
		 **/
		virtual pAbstractColor getActiveColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the background color when the text label is active.
		 **/
		virtual pAbstractColor getActiveBackgroundColor();

		/**
		 * @return An AbstractColor object.
		 * @brief Returns the border color.
		 **/
		virtual pAbstractColor getBorderColor();

		/**
		 * @brief Adjusts the size of the TextField depending on the content.
		 **/
		virtual void adjustSize();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the text field background and text.
		 **/
		virtual void draw(gcn::Graphics* graphics);

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the text field border.
		 **/
		virtual void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<TextField> pTextField;
}

#endif
