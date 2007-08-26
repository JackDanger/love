#include "GUICircleButton.h"
#include "EventListener.h"

#include "MessageEvent.h"
#include "GUIGameListElement.h"

#include "love.h"
#include "Core.h"
#include "Mouse.h"

namespace love
{

	GUICircleButton::GUICircleButton(AbstractImage * image, const string & label, pEvent command, Font * font)
	{
		this->font = font;
		this->label = label;
		this->command = command;
		this->image = image;
		this->bg = true;
		enable = true;
	}

	GUICircleButton::~GUICircleButton()
	{
	}

	void GUICircleButton::setLabel(const string & label)
	{
		this->label = label;
	}

	void GUICircleButton::update(float dt)
	{
		this->bg = false;

		const Mouse & mouse = core->getMouse();

		float mx = mouse.getX();
		float my = mouse.getY();

		float x = getX();
		float y = getY();

		if(mx > x && mx < x + width + 15 && my > y && my < y + height + 5 && mouse.getButtons() == 0)
		{
			this->bg = true;
		}
	}

	void GUICircleButton::render()
	{

		if(!enable) return;

		if(bg)
		{
			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(15, 5, 0);
			glPushAttrib(GL_CURRENT_BIT);
			glColor4ub(255, 255, 255, 50);
			glBegin(GL_QUADS);
				glVertex2f(0, 0);
				glVertex2f(0, height);
				glVertex2f(width, height);
				glVertex2f(width, 0);
			glEnd();
			glPopAttrib();
			glPopMatrix();
		}

		// At 0
		image->render();

		if(font != 0)
		{
			glTranslatef(34, 21, 0);
			font->print(label);
			glTranslatef(-34, -21, 0);
		}


	}

	int GUICircleButton::load()
	{
		return 1;
	}

	void GUICircleButton::unload()
	{

	}

	void GUICircleButton::mousePressed(float x, float y, int button)
	{
		if(!enable) return;

		const Mouse & mouse = core->getMouse();

		float mx = mouse.getX();
		float my = mouse.getY();

		if(mx > getX() && mx < getX() + width + 15 && my > getY() && my < getY() + height + 5 && button == LOVE_MOUSE_LEFT)
		{
			//pMessageEvent e(new MessageEvent(command));
			eventFired(command);
		}
	}


}// love
