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

	void GUIContainer::add(const pMenu * menu)
	{
		gcn::Container::add(menu->get());
	}

	void GUIContainer::remove(const pMenu * menu)
	{
		gcn::Container::remove(menu->get());
	}
}