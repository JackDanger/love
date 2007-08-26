#include "Viewport.h"

#include "love_gl.h"

namespace love 
{


	Viewport::Viewport()
	{
	}

	Viewport::Viewport(float x, float y, float xMax, float yMax, float width, float height)
	{
		setPosition(x, y);
		this->xMax = xMax;
		this->yMax = yMax;
		this->width = width;
		this->height = height;

		half_width = width/2;
		half_height = height/2;

		syncing = false;
	}

	Viewport::~Viewport()
	{
	}

	void Viewport::update(float dt)
	{
		// Look at the sync point if we're in sync mode.
		if(syncing)
			lookAt(*xSync, *ySync);

		// Make sure we're looking at something we're allowed to 
		// look at.
		if(getX() < xMin)
			setX(xMin);
		if(getX() > xMax)
			setX(xMax);

		if(getY() < yMin)
			setY(yMin);
		if(getY() > yMax)
			setY(yMax);

	}


	void Viewport::translate()
	{
		glTranslatef(-getX(), -getY(), 0.0f);
	}

	float Viewport::getWidth()
	{
		return width;
	}

	float Viewport::getHeight()
	{
		return height;
	}

	void Viewport::reset()
	{
		setPosition(0,0);
	}

	void Viewport::setConstraints(float xMin, float xMax, float yMin, float yMax)
	{
		this->xMax = xMax;
		this->yMax = yMax;
		this->xMin = xMin;
		this->yMin = yMin;
	}

	void Viewport::lookAt(float x, float y)
	{
		setPosition(x - half_width, y - half_height);
	}

	void Viewport::sync(float *xSync, float *ySync)
	{
		this->syncing	= true;
		this->xSync		= xSync;
		this->ySync		= ySync;
	}

	void Viewport::deSync()
	{
		this->syncing = false;
	}


}// love