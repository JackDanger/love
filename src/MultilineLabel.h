#ifndef LOVE_MULTILINE_LABEL_H
#define LOVE_MULTILINE_LABEL_H

#include "Label.h"

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
	class MultilineLabel : public Label
	{
	protected:
		std::vector<std::string> lines;

	public:
		/**
		 * @param caption The label's caption.
		 * @brief Constructor. Initializes the variables and aligns the caption to the middle of the label.
		 **/
		MultilineLabel(const std::string & caption = "");

		/**
		 * @brief Deconstructor. Does nothing.
		 **/
		virtual ~MultilineLabel();

		/**
		 * @param caption The text in the multiline label.
		 * @brief Sets the caption.
		 **/
		virtual void setCaption(const std::string & caption);

		/**
		 * @return The new height.
		 * @brief Adjusts the content in the label. Splitting the lines depending on the width of the label.
		 **/
		virtual int adjustContent();

		/**
		 * @brief Adjusts the size of the label according to the size of the caption. 
				  If the width is already set it only adjusts the height. It also splits the lines and calculates the width and height.
		 **/
		virtual void adjustSize();

		/**
		 * @param graphics A GUIchan Graphics object.
		 * @brief Draws the label background and text.
		 **/
		virtual void draw(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<MultilineLabel> pMultilineLabel;
}

#endif
