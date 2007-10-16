#include "GUIEvent.h"

namespace love
{
	GUIEvent::GUIEvent()
	{
		source = 0;
		name = "";
		setType(LOVE_TYPE_GUI_EVENT);
	}

	GUIEvent::GUIEvent(gcn::Widget * widget)
	{
		source = widget;
		name = widget->getActionEventId();
	}

	GUIEvent::~GUIEvent()
	{}

	gcn::Widget * GUIEvent::getSource()
	{
		return source;
	}

	const char * GUIEvent::getName()
	{
		return name.c_str();
	}

	void GUIEvent::setSource(gcn::Widget * widget)
	{
		source = widget;
	}

	void GUIEvent::setName(string name)
	{
		this->name = name;
	}
}