#include "GUI.h"

namespace love
{
	void GUI::handleMousePressed(const gcn::MouseInput& mouseInput)
	{
		int x = mouseInput.getX();
		int y = mouseInput.getY();
		gcn::Widget * temp = mTop->getWidgetAt(x, y); // this will always be the top GUIContainer (or nothing)
		if(temp != 0)
			temp = temp->getWidgetAt(x, y);
		if(temp == 0)
			this->mFocusHandler->focusNone();
		gcn::Gui::handleMousePressed(mouseInput);
	}

	GUI::GUI() : gcn::Gui()
	{
	}

	GUI::~GUI()
	{
	}

	bool GUI::hasFocus()
	{
		gcn::Widget * temp = mFocusHandler->getFocused();
		if(temp == 0)
			return false;
		else
			return true;
	}
}
