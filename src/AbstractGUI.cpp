#include "AbstractGUI.h"
#include "Core.h"
#include "love.h"

namespace love
{
	AbstractGUI::AbstractGUI()
	{
		gui = 0;
		guifont = 0;
		graphics = 0;
		top = 0;
	}

	AbstractGUI::~AbstractGUI()
	{
		if(gui != 0) delete gui;
		if(guifont != 0) delete guifont;
		if(graphics != 0) delete graphics;
		if(top != 0) delete top;
	}

	void AbstractGUI::action(const gcn::ActionEvent& actionEvent)
	{
		//printf("ActionEvent: %s\n", actionEvent.getId().c_str());
		pGUIEvent temp(new GUIEvent(actionEvent.getSource()));
		temp->setType(LOVE_TYPE_GUI_EVENT);
		temp->setName(actionEvent.getId());
		core->eventFired(temp);
	}

	void AbstractGUI::add(const pMenu * menu)
	{
		top->add(menu->get());
	}

	void AbstractGUI::add(gcn::Widget * widget)
	{
		top->add(widget);
	}

	void AbstractGUI::remove(const pMenu * menu)
	{
		top->remove(menu->get());
	}

	void AbstractGUI::remove(gcn::Widget * widget)
	{
		top->remove(widget);
	}

	void AbstractGUI::clear()
	{
		top->clear();
		top->add(new Label(" ")); // Worst. Bugfix. Ever.
	}

	pAbstractFont AbstractGUI::getFont()
	{
		return font;
		//return text->getFont();
	}

	pAbstractColor AbstractGUI::getColor()
	{
		return color;
		//return text->getColor();
	}

	int AbstractGUI::init()
	{
		return LOVE_OK;
	}

	void AbstractGUI::render()
	{
		gui->draw();
	}

	void AbstractGUI::update(float dt)
	{
		gui->logic();
	}
}
