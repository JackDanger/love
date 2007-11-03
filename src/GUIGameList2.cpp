#include "GUIGameList2.h"
#include "Game.h"

#include "MessageEvent.h"
#include "love_keys.h"
#include "love.h"
#include "Core.h"
#include "DisplayMode.h"

#include "Globals.h"

#include <cmath>

#define PI 3.14159265
#define TWOPI PI*2
#define DEG PI/180

namespace love
{

	GUIGameList2::GUIGameList2()
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

	GUIGameList2::~GUIGameList2()
	{
	}


	void GUIGameList2::keyPressed(int key)
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

	void GUIGameList2::keyReleased(int key)
	{

	}

	void GUIGameList2::mousePressed(float x, float y, int button)
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
					//printf("Seek: %s, a: %f\n", gameListElements[i].getGame()->getName().c_str(), reverse(ci * step));
					



					//float dist = 0.50f - t;
					//viewport += dist;

					


				}
			}

			if(ci != -1)
			{

				//float t = getT(ci);
				float s = center_t - (ci * space_t);
				//printf("T: %f\n", t);
				//printf("Viewport: %f\n", s);
				

				//float s = viewport - (t - center_t);
				seek(s);

				//printf("Seek to: %f\n", s);
			}
		}
	}

	vector<GUIGameListElement> & GUIGameList2::getGameListElements()
	{
		return gameListElements;
	}

	void GUIGameList2::addGameListElement(GUIGameListElement e)
	{
		e.setParent(this);
		gameListElements.push_back(e);

	}

	float GUIGameList2::speedFunc(float t)
	{
		if(t < 0 || t > 1) return 0;
	
		setX(2 * t - 1);

		float amp = 2.0f;

		return amp*pow(getX(), 4)-2*amp*getX()*getX()+amp;
	}

	void GUIGameList2::setSpeed(float speed)
	{
		seeking = false;
		velocity.setX(speed);
	}

	float GUIGameList2::getSpeed() const
	{
		return velocity.getX();
	}

	float GUIGameList2::angleFunc(float t)
	{
		float x = -2*pow(t, 3) + 3 * t * t;

		/**
		float amp = 2.0f;
		float f = amp*pow(x, 4)-2*amp*x*x+amp;
		**/


		float tmp = seekSrc + seekDelta * x;
		return tmp;
	}

	void GUIGameList2::setViewport(float t)
	{

		float raw = viewport_max + ((viewport_min - viewport_max) * t);

		viewport = raw;
		//printf("Setting viewport: %f\n", viewport);
	}

	void GUIGameList2::next(float speed)
	{
		//if(seeking) return;

		if(viewport >= viewport_max) return;

		if(!seeking)
			seek(viewport + space_t, speed);
		else
			seek(seekDest + space_t, speed);
	}

	void GUIGameList2::previous(float speed)
	{
		//if(seeking) return;

		if(viewport <= viewport_min) return;

		if(!seeking)
			seek(viewport - space_t, speed);
		else
			seek(seekDest - space_t, speed);
	}

	int GUIGameList2::sign(float n)
	{
		return (n < 0 ? -1 : 1);
	}

	float GUIGameList2::shortest(float a1, float a2)
	{
		//float d1 = abs(a2 - a1);
		//float d2 = d1 - TWOPI;
		float d1 = a1 - a2;
		float d2 = (float)(TWOPI - fabs(d1));
		return fabs(d1) < fabs(d2) ? d1 : d2;
	}


	void GUIGameList2::seek(float t, float time)
	{
		

		seekSrc = viewport;
		seekDest = t;
		seekDelta = seekDest - seekSrc;
		
		seekTime = 0;
		seekMax = time;

		seeking = (seekDelta != 0);

	}

	bool GUIGameList2::seekGame(const string & game, float time)
	{
		int size = (int)gameListElements.size();

		// Update list elements
		for(int i=0;i<size;i++)
		{
			if(gameListElements[i].getGame()->getName() == game)
			{
				float s = center_t - (i * space_t);
				seek(s, time);
				return true;
			}
		}

		return false;
	}

	float GUIGameList2::getCurrentPosition()
	{
		return (viewport - viewport_max)/(viewport_min - viewport_max);
	}

	float GUIGameList2::reverse(float angle)
	{
		return clampa((float)(TWOPI - angle));
	}

	void GUIGameList2::update(float dt)
	{

		float size = (float)this->size;



		
		
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
				this->viewport = angleFunc(t);
			}else
			{
				seeking = false;
				this->viewport = seekDest;
			}

		}
		else
		{
			/**
			if(abs(acceleration.getX()) > 0.001)
			{
				acceleration.setX(acceleration.getX() * (1 - 2 * dt));
			}else setAcceleration(0, 0);

			if(abs(velocity.getX()) > 0.001)
			{
				velocity.setX(velocity.getX() * (1 - 4 * dt));
			}else setVelocity(0, 0);

			velocity.setX(velocity.getX() + acceleration.getX() * dt);
			orientation += velocity.getX() * dt;

			float a = orientation;

			float closest = 9999999;
			

			for(int i=0;i<size;i++)
			{
				float dist = abs(shortest(clampa(i * step), clampa(orientation)));
				if(dist < closest)
				{
					ci = i;
					closest = dist;
				}
				a+=step;
			}

			if(abs(velocity.getX()) < 0.1)
			{
				seek(ci * step, 0.5);
			}
			**/

		}



		if(viewport > viewport_max) viewport = viewport_max;
		if(viewport < viewport_min) viewport = viewport_min;

		orientation = clampa(orientation);


	}

	float GUIGameList2::clampa(float angle)
	{
		if(angle > TWOPI) return (float)(angle - TWOPI);
		if(angle < 0) return (float)(angle + TWOPI);
		return angle;
	}

	float GUIGameList2::scale(float t)
	{

		//if( t < 0 || t > 1) return 0;

		float x = -1 + 2 * t;

		float s = -x*x + 1;

		//if(s < 0.7) s = 0.7;

		return s;
	}

	Vector GUIGameList2::position(float t)
	{

		if( t < 0 || t > 1) 
			return Vector(-2000, -2000);

		//float x = -cos(t * (float)TWOPI) * 100 + 270;
		//float tyx = -1 + 2 * t;
		//float ty = -2*pow(t, 3) + 3 * t * t;
		//float y = 0 + ( (this->height) * ty);

		float x = 200;
		float ty = -2*pow(t, 3) + 3 * t * t;
		float y = 0 + ( (this->height) * ty);

		return Vector(x, y);
	}

	float GUIGameList2::buttonalpha(float t)
	{
		float x = -1 + 2 * t;

		float a = -10*x*x + 1;

		return a;
	}


	float GUIGameList2::alpha(float t)
	{
		float x = -1 + 2 * t;

		float a = -x*x + 1;

		return a;
	}



	float GUIGameList2::getT(int i)
	{
		return (i * space_t) + viewport;
	}

	void GUIGameList2::render()
	{

		glLoadIdentity();

		

		int size = (int)gameListElements.size();

		//int start = viewport/50;
		//int end = start + (viewport_size + 1) * 2;

		// Space for each entry
		//space_t = 1.0f / 4.0f;

		for(int i=0;i<size;i++)
		{


			// Calculate t
			float t = getT(i);

			if(t < 0 || t > 1) continue;

			Vector pos = position(t);
			float s = scale(t);
			float ba = buttonalpha(t);
			float a = alpha(t);


			glColor4f(1, 1, 1, a);

			gameListElements[i].buttonsAlpha = ba;
			gameListElements[i].setPosition(getX() + pos.getX(), getY() + pos.getY());
			gameListElements[i].setScale(s);


			gameListElements[i].render();




		}



	}

	float GUIGameList2::getStep() const
	{
		return step;
	}

	int GUIGameList2::load()
	{

		const DisplayMode & dm = core->getDisplayMode();
		this->width = (float)dm.getWidth();
		this->height = (float)dm.getHeight();

		for(unsigned int i=0;i<gameListElements.size();i++)
		{
			gameListElements[i].setParent(this);
			gameListElements[i].load();
		}


		setSpacing(1.0f / 5.0f);


		return LOVE_OK;
	}

	void GUIGameList2::setSpacing(float st)
	{
		this->size = (int)gameListElements.size();

		viewport_size = 2;
		center_t = 0.5f;
		space_t = st;
		
		viewport_max = center_t;
		viewport_min = center_t - (size-1) * space_t;

		if(size > 2)
		{
			int half = (int)(size/2);
			viewport = center_t - half * space_t;
		} 
		else viewport = viewport_min;
	}

	void GUIGameList2::unload()
	{
		for(unsigned int i=0;i<gameListElements.size();i++)
			gameListElements[i].unload();

		gameListElements.clear();
	}


}// love
