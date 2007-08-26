#include "GUIRadialKnob.h"


#include "Vextor.h"
#include "GUIGameList2.h"

#include "love.h"
#include "Core.h"
#include "Mouse.h"


#define PI 3.14159265
#define TWOPI PI*2
#define DEG PI/180

namespace love
{

	GUIRadialKnob::GUIRadialKnob(AbstractImage * big, AbstractImage * small, Font * font)
		: big(big), small(small), font(font)
	{
		bigRadius = 51;
		smallRadius = 7;
		lock = false;
		control = 0;
		orientation = 0;
	}

	GUIRadialKnob::~GUIRadialKnob()
	{
	}

	float GUIRadialKnob::angle(const Vextor & v1, const Vextor & v2) const
	{
		float cosine = (v1 * v2)/(v1.getLength() * v2.getLength());

		if (cosine > 1) cosine = 1;
		else if (cosine < -1) cosine = -1;

		if (v1.getX() * v2.getY() - v1.getY() * v2.getX() < 0)
			return -acos(cosine);
		else
			return acos(cosine);
	}

	float GUIRadialKnob::clampa(float angle)
	{
		if(angle > TWOPI) return (float)(angle - TWOPI);
		if(angle < 0) return (float)(angle + TWOPI);
		return angle;
	}

	void GUIRadialKnob::update(float dt)
	{

		// Get a reference to the mouse.
		const Mouse & mouse = core->getMouse();

		if(lock)
		{

			Vextor a(getX(), getY());
			Vextor m(mouse.getX(), mouse.getY());

			Vextor z(1, 0);
			Vextor ma = a - m;

			float next_angle = (float)(-angle(ma, z)) + (float)PI;

			if(orientation <= PI/2 && next_angle > PI)
				orientation = 0;
			else if(orientation >= 3/2 * PI && next_angle < PI/2)
				orientation = 2 * (float)PI;
			else
				orientation = next_angle;
			
			//if(orientation >= 0 && orientation )

			//if(orientation < 0) orientation = 0;
			//if(orientation > 2 * PI) orientation = 2 *PI;

			if(control != 0)
			{
				control->setViewport(getOrientation()/(2*(float)PI));
			}

		}

		if(lock && mouse.getButtons() == 0)
		{
			core->printf("Lock released.\n");
			lock = false;
		}
	}

	void GUIRadialKnob::mousePressed(float x, float y, int button)
	{
		
		if(button == LOVE_MOUSE_LEFT)
		{

			// Get a reference to the mouse.
			const Mouse & mouse = core->getMouse();

			float px = getX() + cos(orientation) * bigRadius;
			float py = getY() + sin(orientation) * bigRadius;

			Vextor a(px, py);
			Vextor m(mouse.getX(), mouse.getY());
			Vextor ma = a - m;

			float dist = ma.getLength();

			if( dist < smallRadius)
			{
				core->printf("Dist: %.2f\n", dist);
				lock = true;
			}
			

		}

	}

	void GUIRadialKnob::render()
	{
		glPushMatrix();
		glTranslatef(-big->getWidth() / 2.0f, -big->getHeight() /2.0f, 0);
		big->render();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-small->getWidth() / 2.0f, -small->getHeight() /2.0f, 0);

		float x = cos(orientation) * bigRadius;
		float y = sin(orientation) * bigRadius;

		glTranslatef(x, y, 0);

		small->render();
		glPopMatrix();

		glPushMatrix();

			char buffer[20];
			sprintf(buffer, "%.0f°", orientation * 180/3.14159265);
			string buf(buffer);

			glTranslatef(-10, 5, 0);
			font->print(buf);
		glPopMatrix();

		
	}

	void GUIRadialKnob::setControl(GUIGameList2 * control)
	{
		this->control = control;
	}


}// love
