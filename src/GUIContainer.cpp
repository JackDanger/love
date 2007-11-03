#include "GUIContainer.h"

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

	void GUIContainer::add(const pAbstractMenu * menu)
	{
		switch(menu->get()->getMenuType())
		{
		case AbstractMenu::LOVE_MENU_DEFAULT:
			gcn::Container::add(boost::dynamic_pointer_cast<Menu, AbstractMenu>(*menu).get());
			break;
		case AbstractMenu::LOVE_MENU_WINDOW:
			break;
		case AbstractMenu::LOVE_MENU_SCROLLING:
			break;
		}
	}

	void GUIContainer::remove(const pAbstractMenu * menu)
	{
		switch(menu->get()->getMenuType())
		{
		case AbstractMenu::LOVE_MENU_DEFAULT:
			gcn::Container::remove(boost::dynamic_pointer_cast<Menu, AbstractMenu>(*menu).get());
			break;
		case AbstractMenu::LOVE_MENU_WINDOW:
			break;
		case AbstractMenu::LOVE_MENU_SCROLLING:
			break;
		}
	}
}
