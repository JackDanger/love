#include "TextBox.h"

namespace love
{
	TextBox::TextBox(const char * text)
	{
		gcn::TextBox();
		gcn::TextBox::setText(text);
	}

	TextBox::~TextBox()
	{ }

	void TextBox::setSize(int width, int height)
	{
		gcn::TextBox::setSize(width, height);
	}

	void TextBox::setWidth(int width)
	{
		gcn::TextBox::setWidth(width);
	}

	void TextBox::setHeight(int height)
	{
		gcn::TextBox::setHeight(height);
	}

	void TextBox::setBorderSize(unsigned int size)
	{
		gcn::TextBox::setBorderSize(size);
	}

	void TextBox::setText(const char * text)
	{
		gcn::TextBox::setText(text);
	}

	void TextBox::setName(const char * name)
	{
		gcn::TextBox::setActionEventId(name);
	}

	void TextBox::setCaretColumn(int column)
	{
		gcn::TextBox::setCaretColumn(column);
	}

	void TextBox::setCaretPosition(unsigned int position)
	{
		gcn::TextBox::setCaretPosition(position);
	}

	void TextBox::setCaretRow(int row)
	{
		gcn::TextBox::setCaretRow(row);
	}

	void TextBox::setCaretRowColumn(int row, int column)
	{
		gcn::TextBox::setCaretRowColumn(row, column);
	}

	void TextBox::setEditable(bool editable)
	{
		gcn::TextBox::setEditable(editable);
	}

	void TextBox::setTextRow(int row, const char * text)
	{
		gcn::TextBox::setTextRow(row, text);
	}

	void TextBox::setActiveColor(const pAbstractColor * color)
	{
		activeColor = (*color);
	}

	void TextBox::setActiveBackgroundColor(const pAbstractColor * color)
	{
		activeBackgroundColor = (*color);
	}

	int TextBox::getWidth()
	{
		return gcn::TextBox::getWidth();
	}

	int TextBox::getHeight()
	{
		return gcn::TextBox::getHeight();
	}

	unsigned int TextBox::getBorderSize()
	{
		return gcn::TextBox::getBorderSize();
	}

	const char * TextBox::getText()
	{
		return gcn::TextBox::getText().c_str();
	}

	const char * TextBox::getName()
	{
		return gcn::TextBox::getActionEventId().c_str();
	}

	unsigned int TextBox::getCaretColumn() const
	{
		return gcn::TextBox::getCaretColumn();
	}

	unsigned int TextBox::getCaretPosition() const
	{
		return gcn::TextBox::getCaretPosition();
	}

	unsigned int TextBox::getCaretRow() const
	{
		return gcn::TextBox::getCaretRow();
	}

	unsigned int TextBox::getNumberOfRows() const
	{
		return gcn::TextBox::getNumberOfRows();
	}

	const char * TextBox::getRow(int row) const
	{
		return gcn::TextBox::getTextRow(row).c_str();
	}

	bool TextBox::isEditable () const
	{
		return gcn::TextBox::isEditable();
	}

	pAbstractColor TextBox::getActiveColor()
	{
		return activeColor;
	}

	pAbstractColor TextBox::getActiveBackgroundColor()
	{
		return activeBackgroundColor;
	}

	void TextBox::adjustSize()
	{
		gcn::TextBox::adjustSize();
	}

	void TextBox::draw(gcn::Graphics* graphics)
	{
		if(isFocused() && activeColor.get() != 0)
			gcn::TextBox::setForegroundColor(gcn::Color(activeColor->getRed(),activeColor->getGreen(),activeColor->getBlue(),activeColor->getAlpha()));
		else if(color.get() != 0)
			gcn::TextBox::setForegroundColor(gcn::Color(color->getRed(),color->getGreen(),color->getBlue(),color->getAlpha()));
		
		if(isFocused() && activeBackgroundColor.get() != 0)
			gcn::TextBox::setBackgroundColor(gcn::Color(activeBackgroundColor->getRed(),activeBackgroundColor->getGreen(),activeBackgroundColor->getBlue(),activeBackgroundColor->getAlpha()));
		else if(backgroundColor.get() != 0)
			gcn::TextBox::setBackgroundColor(gcn::Color(backgroundColor->getRed(),backgroundColor->getGreen(),backgroundColor->getBlue(),backgroundColor->getAlpha()));
		gcn::TextBox::draw(graphics);
	}

	void TextBox::drawBorder(gcn::Graphics* graphics)
	{
		int width = getWidth() + getBorderSize() * 2 - 1;
		int height = getHeight() + getBorderSize() * 2 - 1;

		if(borderColor.get() != 0)
			graphics->setColor(gcn::Color(borderColor->getRed(),borderColor->getGreen(),borderColor->getBlue(),borderColor->getAlpha()));
		else
			graphics->setColor(gcn::Color(0x000000));
		
		for (unsigned int i = 0; i < getBorderSize(); ++i)
		{
			graphics->drawLine(i,i, width - i, i);
			graphics->drawLine(i,i + 1, i, height - i - 1);
			graphics->drawLine(width - i,i + 1, width - i, height - i);
			graphics->drawLine(i,height - i, width - i - 1, height - i);
		}
	}
}