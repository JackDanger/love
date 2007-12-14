#include "GUIGameList.h"
#include "Game.h"

#include "MessageEvent.h"
#include "love_keys.h"

#include "Globals.h"

#include <cmath>

#define PI 3.14159265
#define TWOPI PI*2
#define DEG PI/180

using std::vector;

namespace love
{

	GUIGameList::GUIGameList()
	{
		this->setAcceleration(0, 0);
		this->setOrientation(0);
		this->setVelocity(0, 0);

		radius = 400;
		seeking = false;

		ci = 0;

		this->width = 1024;
		this->height = 768;

		setParent(0);
		
	}

	GUIGameList::~GUIGameList()
	{
	}

	void GUIGameList::keyPressed(int key)
	{

		if(key == LOVE_KEY_RETURN)
		{


			int index = (int)(gameListElements.size() - (int)floor(orientation/step + 0.5f));
			
			if(index == (int)gameListElements.size()) index = 0;

			printf("Starting game (%p), (%s)", gameListElements[index].getGame(), gameListElements[index].getGame()->getName().c_str());
			pMessageEvent e(new MessageEvent(gameListElements[index].getGame()->getName()));

			//if(eventListener != 0)
			//	eventListener->eventFired(e);
		}
	}

	void GUIGameList::keyReleased(int key)
	{

	}

	void GUIGameList::mousePressed(float x, float y, int button)
	{

		// Send message to all list elements
		int size = (int)gameListElements.size();
		for(int i=0;i<size;i++) gameListElements[i].mousePressed(x, y, button);

		if(button == LOVE_MOUSE_LEFT)
		{
			int ci = -1;

			for(int i=0;i<size;i++)
			{

				// Also, check if we should seek to some element
				float s = gameListElements[i].getScale();
				float tw = 200.0f * s;
				float th = 150.0f * s;
				float gx = gameListElements[i].getX() - tw / 2.0f;
				float gy = gameListElements[i].getY() - th / 2.0f;
				float gw = 200 * s;
				float gh = 150 * s;

				if(x > gx && x < gx + gw && y > gy && y < gy + gh)
				{
					ci = i;
					printf("Seek: %s, a: %f\n", gameListElements[i].getGame()->getName().c_str(), reverse(ci * step));
				}
			}

			if(ci != -1)
			{
				seek(reverse(ci * step), 0.5);
			}
		}
	}

	vector<GUIGameListElement> & GUIGameList::getGameListElements()
	{
		return gameListElements;
	}

	void GUIGameList::addGameListElement(GUIGameListElement e)
	{
		e.setParent(this);
		gameListElements.push_back(e);
	}

	float GUIGameList::speedFunc(float t)
	{
		if(t < 0 || t > 1) return 0;
	
		setX(2 * t - 1);

		float amp = 2.0f;

		return amp*pow(getX(), 4)-2*amp*getX()*getX()+amp;
	}

	void GUIGameList::setSpeed(float speed)
	{
		seeking = false;
		velocity.setX(speed);
	}

	float GUIGameList::getSpeed() const
	{
		return velocity.getX();
	}

	float GUIGameList::angleFunc(float t)
	{
		float x = -2*pow(t, 3) + 3 * t * t;

		/**
		float amp = 2.0f;
		float f = amp*pow(x, 4)-2*amp*x*x+amp;
		**/


		float tmp = seekSrc + seekDelta * x;
		return tmp;
	}


	void GUIGameList::next()
	{
		//if(seeking) return;

		seek(orientation + step, 0.2f);
	}

	void GUIGameList::previous()
	{
		//if(seeking) return;

		seek(orientation - step, 0.2f);
	}

	int GUIGameList::sign(float n)
	{
		return (n < 0 ? -1 : 1);
	}

	float GUIGameList::shortest(float a1, float a2)
	{
		//float d1 = abs(a2 - a1);
		//float d2 = d1 - TWOPI;
		float d1 = a1 - a2;
		float d2 = (float)(TWOPI - fabs(d1)); //ah, removing warnings is fun
		return fabs(d1) < fabs(d2) ? d1 : d2;
	}

	void GUIGameList::seek(float angle, float seekMax)
	{


		this->setAcceleration(0, 0);
		this->setVelocity(0, 0);

		seekDest = angle;
		seekSrc = orientation;
		seekDelta = shortest(seekDest, seekSrc);

		seekTime = 0;
		this->seekMax = seekMax;

		seeking = seekDelta != 0;
	}

	float GUIGameList::reverse(float angle)
	{
		return clampa((float)(TWOPI - angle));
	}

	void GUIGameList::update(float dt)
	{

		float size = (float)gameListElements.size();
		
		// Get angle step
		step = (float)(((float)360 / ((float)size)) * DEG);

		// Update list elements
		for(int i=0;i<size;i++)
		{
			gameListElements[i].update(dt);
		}

		if(seeking)
		{

			seekTime += dt;
			float t = seekTime/seekMax;

			if(t >= 0 && t <= 1)
			{
				this->orientation = angleFunc(t);
			}else
			{
				seeking = false;
				this->orientation = seekDest;
			}

		}
		else
		{
			if(fabs(acceleration.getX()) > 0.001)
			{
				acceleration.setX(acceleration.getX() * (1 - 2 * dt));
			}else setAcceleration(0, 0);

			if(fabs(velocity.getX()) > 0.001)
			{
				velocity.setX(velocity.getX() * (1 - 4 * dt));
			}else setVelocity(0, 0);

			velocity.setX(velocity.getX() + acceleration.getX() * dt);
			orientation += velocity.getX() * dt;

			float a = orientation;

			float closest = 9999999;
			

			for(int i=0;i<size;i++)
			{
				float dist = fabs(shortest(clampa(i * step), clampa(orientation)));
				if(dist < closest)
				{
					ci = i;
					closest = dist;
				}
				a+=step;
			}

			if(fabs(velocity.getX()) < 0.1)
			{
				seek(ci * step, 0.5);
			}

		}

		orientation = clampa(orientation);

	}

	float GUIGameList::clampa(float angle)
	{
		if(angle > TWOPI) return (float)(angle - TWOPI);
		if(angle < 0) return (float)(angle + TWOPI);
		return angle;
	}

	float GUIGameList::scale(float angle)
	{
		float s = fabs(sin(angle));

		return 1 - s/2;
	}

	void GUIGameList::render()
	{


		float size = (float)gameListElements.size();

		

		this->radius = size * 26;

		float xamp = size / 16;

		this->setX(370 - radius * xamp);
		this->setY(768/2);

		float a = orientation;



		glLoadIdentity();

		glTranslatef(getX(), getY(), 0);
		glColor4ub(255, 255, 255, 255);

		for(int i=0;i<size;i++)
		{

			// Get coordinates
			float x = cos(a) * radius * xamp;
			float y = sin(a) * radius;

			gameListElements[i].setPosition(getX() + x, getY() + y);

			if((getX() + x) < 0 || (getX() + x) > 1024   ||   (getY() + y) < -100 || (getY() + y) > 900)
			{
				a += step;
				continue;
			}

			float s = scale(a);

			gameListElements[i].setScale(s);
			gameListElements[i].setOrientation(a - orientation);

			float t = s * s;

			// Get button alpha
			float dist = fabs((height/2.0f) - (getY() + y));
			float ba = 1.0f - dist/70.0f;

			if(ba < 0) ba = 0;

			gameListElements[i].buttonsAlpha = ba;

			glPushMatrix();
			glTranslatef(x, y, 0);
			glColor4f(1, 1, 1, t);
			glScalef(s, s, 0);
			gameListElements[i].render();
			glPopMatrix();



			a += step;
		}



	}

	float GUIGameList::getStep() const
	{
		return step;
	}

	int GUIGameList::load()
	{
		for(unsigned int i=0;i<gameListElements.size();i++)
		{
			gameListElements[i].setParent(this);
			gameListElements[i].load();
		}

		return 1;
	}

	void GUIGameList::unload()
	{
		for(unsigned int i=0;i<gameListElements.size();i++)
			gameListElements[i].unload();
	}


}// love
