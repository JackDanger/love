#include "GUIContainer.h"
#include "Core.h"
#include "love.h"

namespace love
{
	GUIContainer::GUIContainer()
	{
		gcn::Container();
	}

	GUIContainer::~GUIContainer()
	{
		clear();
	}

	void GUIContainer::add(const pAbstractMenu & menu)
	{
		switch(menu->getMenuType())
		{
		case AbstractMenu::LOVE_MENU_DEFAULT:
			gcn::Container::add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(menu).get());
			break;
		case AbstractMenu::LOVE_MENU_WINDOW:
			gcn::Container::add(boost::dynamic_pointer_cast<WindowMenu, AbstractMenu>(menu).get());
			break;
		case AbstractMenu::LOVE_MENU_SCROLL:
			gcn::Container::add(boost::dynamic_pointer_cast<ScrollMenu, AbstractMenu>(menu).get());
			break;
		}
	}

	void GUIContainer::remove(const pAbstractMenu & menu)
	{
		switch(menu->getMenuType())
		{
		case AbstractMenu::LOVE_MENU_DEFAULT:
			gcn::Container::remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(menu).get());
			break;
		case AbstractMenu::LOVE_MENU_WINDOW:
			gcn::Container::remove(boost::dynamic_pointer_cast<WindowMenu, AbstractMenu>(menu).get());
			break;
		case AbstractMenu::LOVE_MENU_SCROLL:
			gcn::Container::remove(boost::dynamic_pointer_cast<ScrollMenu, AbstractMenu>(menu).get());
			break;
		}
	}

	bool GUIContainer::hasFocus()
	{
		return core->getGUI()->hasFocus();
	}
}
