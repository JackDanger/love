#include "Vector.h"
#include "Point.h"

namespace love 
{


	Vector::Vector()
	{
		xLength = 0;
		yLength = 0;
		setPosition(0,0);
		setType(LOVE_TYPE_VECTOR);
	}

	Vector::Vector(float xlen, float ylen)
	{
		setPosition(0,0);
		xLength = xlen;
		yLength = ylen;
		setType(LOVE_TYPE_VECTOR);
	}

	Vector::Vector(float xpos, float ypos, float xlen, float ylen)
	{
		xLength = xlen;
		yLength = ylen;
		setPosition(xpos,ypos);
		setType(LOVE_TYPE_VECTOR);
	}

	Vector::~Vector()
	{
	}

	void Vector::add(Vector & v)
	{
		xLength += v.getXLength();
		yLength += v.getYLength();
	}

	void Vector::sub(Vector & v)
	{
		xLength -= v.getXLength();
		yLength -= v.getYLength();
	}

	void Vector::mul(Vector & v)
	{
		xLength *= v.getXLength();
		yLength *= v.getYLength();
	}

	void Vector::mul(float f)
	{
		xLength *= f;
		yLength *= f;
	}

	void Vector::div(Vector & v)
	{
		xLength /= v.getXLength();
		yLength /= v.getYLength();
	}

	void Vector::div(float f)
	{
		xLength /= f;
		yLength /= f;
	}

	float Vector::dot(Point & p)
	{
		return xLength * p.getX() + yLength * p.getY();
	}

	float Vector::dot(float x, float y)
	{
		return xLength * x + yLength * y;
	}

	float Vector::dot(Vector & v)
	{

		return xLength * v.getXLength() + yLength * v.getYLength();

		/**

		if(getAngle() > v.getAngle()) //sjekker hvor vinkelen er positiv
			return xLength * v.getXLength() + yLength * v.getYLength() * (getAngle() - v.getAngle());
		else
			return xLength * v.getXLength() + yLength * v.getYLength() * (v.getAngle() - getAngle());
			**/
	}

	float Vector::getLength()
	{
		return sqrt(pow(xLength,2) + pow(yLength,2));
	}

	void Vector::normalize()
	{
		float length = getLength();

		if(length > 0)
			div(getLength());
	}

	float Vector::getAngle() 
	{
			if (xLength > 0 && yLength >= 0) {
				// 1. kvadrant.
				return (float)atan(yLength / xLength);
			}else if (xLength == 0 && yLength > 0) {
				// Dele på null er tull.
				return (float)(M_PI / 2);
			}else if (xLength < 0 && yLength > 0) {
				// 2. kvadrant. 
				return (float)(M_PI + atan(yLength / xLength));
			}else if(xLength < 0 && yLength <= 0) {
				// 3. kvadrant.
				return (float)(M_PI + atan(yLength / xLength));
			}else if (xLength == 0 && yLength < 0) {
				// Dele på null er tull.
				return (float)(3 * (M_PI / 2));
			}else if(xLength > 0 && yLength < 0) {
				// 4.kvadrant.
				return (float)((2 * M_PI) + atan(yLength / xLength));
			}else {
				// Dette er en null vektor (x=0 og y=0) og vil returnere 2PI.
				// Ensete tilfelle 2PI vil bli returnert av denne metoden.
				return (float)(2 * M_PI);
			} 
	}

	void Vector::updatePos(float x, float y)
	{
		setPosition(x, y);
	}

	float Vector::getXLength()
	{
		return xLength;
	}

	void Vector::setXLength(float xLength)
	{
		this->xLength = xLength;
	}

	float Vector::getYLength()
	{
		return yLength;
	}

	void Vector::setYLength(float yLength)
	{
		this->yLength = yLength;
	}

	void Vector::render()
	{
		// Main line
		glPushMatrix();

			glLoadIdentity();
			glTranslatef(getX(), getY(), 0);

			glBegin(GL_QUADS);
				glVertex2f(-1,-1);
				glVertex2f(-1,1);
				glVertex2f(1,1);
				glVertex2f(1,-1);
			glEnd();

			glBegin(GL_LINES);
				
				
				glVertex2f(0,0);
				glVertex2f(xLength, yLength);					

			glEnd();

		glPopMatrix();


		// First arrow arm
		glPushMatrix();

			glTranslatef(getX()+xLength, getY()+yLength, 0);
			glRotatef(30, 0, 0, 1.0);

			glBegin(GL_LINES);			
				
				glVertex2f(0,0);
				glVertex2f(-(xLength/4), -(yLength)/4);
			glEnd();

		glPopMatrix();

		// Second arrow arm
		glPushMatrix();

			glTranslatef(getX()+xLength, getY()+yLength, 0);
			glRotatef(-30, 0, 0, 1.0);

			glBegin(GL_LINES);			
				
				glVertex2f(0,0);
				glVertex2f(-xLength/4, -yLength/4);
			glEnd();

		glPopMatrix();
	}

	Vector Vector::getNormal()
	{
		return Vector(getX(),getY(),-yLength, xLength);
	}


	bool Vector::operator <(Vector &v)
	{
		return (getLength()<v.getLength());
	}

	bool Vector::operator ==(Vector& v)
	{
		return (getLength()==v.getLength());
	}



	float Vector::operator * (Vector& v)
	{
		return xLength * v.getXLength() + yLength * v.getYLength();
	}

	void Vector::operator *= (Vector& v)
	{
		xLength *= v.getXLength();
		yLength *= v.getYLength();
	}	

	Vector Vector::operator * (float f)
	{
		return Vector(xLength * f, yLength * f);
	}	

	void Vector::operator *= (float f)
	{
		xLength *= f;
		yLength *= f;
	}

	void Vector::operator /= (float f)
	{
		xLength /= f;
		yLength /= f;
	}

	Vector Vector::operator + (Vector& v)
	{
		return Vector(xLength + v.getXLength(), yLength + v.getYLength());
	}

	Vector Vector::operator - (Vector& v)
	{
		return Vector(xLength - v.getXLength(), yLength - v.getYLength());
	}

	void Vector::operator += (Vector& v)
	{
		xLength += v.getXLength();
		yLength += v.getYLength();
	}

	void Vector::operator -= (Vector& v)
	{
		xLength -= v.getXLength();
		yLength -= v.getYLength();
	}



} // love