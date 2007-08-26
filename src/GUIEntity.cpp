#include "GUIEntity.h"

namespace love
{

	GUIEntity::GUIEntity()
	{
		parent = 0;
	}

	GUIEntity::~GUIEntity()
	{
	}

	void GUIEntity::setParent(EventListener * parent)
	{
		this->parent = parent;
	}

	void GUIEntity::mousePressed(float x, float y, int button)
	{

	}

	void GUIEntity::mouseReleased(float x, float y, int button)
	{

	}

	void GUIEntity::keyPressed(int key)
	{
	}

	void GUIEntity::keyReleased(int key)
	{
	}
	
	void GUIEntity::eventFired(pEvent e)
	{
		if(this->parent != 0)
			parent->eventFired(e);
	}

	void GUIEntity::setSize(float width, float height)
	{
		this->width = width;
		this->height = height;
	}


}// love
