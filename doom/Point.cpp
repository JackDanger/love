#include "Point.h"
#include "Vector.h"


namespace love 
{


	Point::Point()
	{
		setType(LOVE_TYPE_POINT);
	}

	Point::Point(float x, float y)
	{
		setPosition(x,y);
		setType(LOVE_TYPE_POINT);
	}

	Point::~Point()
	{
	}

	void Point::render()
	{

		glPointSize(2.0f);

		glPushMatrix();
		glBegin(GL_POINTS);
			glVertex2f(getX(), getY());		
		glEnd();
		glPopMatrix();
	}

	float Point::dot(Point & p)
	{
		return (getX()*p.getX())+(getY()*p.getY());
	}



	Vector Point::to(Point& p)
	{
		return Vector(p.getX() - getX(), p.getY() - getY());
	}



	bool Point::operator == (Point& p)
	{
		return (getX()+getY())==(p.getX()+p.getY());
	}

	bool Point::operator < (Point& p)
	{
		return (getX()+getY())<(p.getX()+p.getY());
	}

	Point Point::operator - (Point & p)
	{
		return Point(getX()-p.getX(), getY()-p.getY());
	}

	void Point::operator -= (Point & p)
	{
		xMove(-p.getX());
		yMove(-p.getY());
	}

	Point Point::operator + (Point & p)
	{
		return Point(getX()+p.getX(), getY()+p.getY());
	}

	void Point::operator += (Vector& v)
	{
		xMove(v.getXLength());
		yMove(v.getYLength());

	}

	void Point::operator -= (Vector& v)
	{
		xMove(-v.getXLength());
		yMove(-v.getYLength());

	}

	Point Point::operator + (Vector & v)
	{
		return Point(getX()+v.getXLength(), getY()+v.getYLength());
	}

	Point Point::operator - (Vector & v)
	{
		return Point(getX()-v.getXLength(), getY()-v.getYLength());
	}

}//love