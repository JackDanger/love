#ifndef LOVE_TEXT_BOX_H
#define LOVE_TEXT_BOX_H

#include "GUIElement.h"

namespace love
{
	/**
	 * @class TextBox
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-11-01
	 * @brief A text boc to be used by the Menu.
	 **/
	class TextBox : public gcn::TextBox, public GUIElement
	{
	protected:
		pAbstractColor activeColor;
		pAbstractColor activeBackgroundColor;

	public:
		TextBox(const string & text = "");
		virtual ~TextBox();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);
		virtual void setText(const string & text);
		virtual void setName(const string & name);

		virtual void setCaretColumn(int column);
		virtual void setCaretPosition(unsigned int position);
		virtual void setCaretRow(int row);
		virtual void setCaretRowColumn(int row, int column);
		virtual void setEditable(bool editable);
		virtual void setTextRow(int row, const string & text);

		virtual void setBackgroundColor(const pAbstractColor & color);
		virtual void setActiveColor(const pAbstractColor & color);
		virtual void setActiveBackgroundColor(const pAbstractColor & color);

		virtual void setFont(const pAbstractFont & font);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();
		virtual const string getText();
		virtual const string & getName();

		virtual unsigned int getCaretColumn() const;
		virtual unsigned int getCaretPosition() const;
		virtual unsigned int getCaretRow() const;
		virtual unsigned int getNumberOfRows() const;
		virtual const string & getRow(int row) const;
		virtual bool isEditable () const;

		virtual pAbstractColor getBackgroundColor();
		virtual pAbstractColor getActiveColor();
		virtual pAbstractColor getActiveBackgroundColor();

		virtual pAbstractFont getFont();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics* graphics);
		virtual void drawBorder(gcn::Graphics* graphics);
	};

	typedef boost::shared_ptr<TextBox> pTextBox;
}

#endif
