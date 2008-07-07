#include "Vector.h"

namespace love_chipmunk
{
	Vector::Vector()
	{
		v = cpv(1, 1);
	}

	Vector::Vector(float a)
	{
		v = cpvforangle(a);
	}

	Vector::Vector(float x, float y)
	{
		v = cpv(x, y);
	}

	Vector::Vector(cpVect t)
		: v(t)
	{
	}

	float Vector::squaredLength() const
	{
		return cpvlengthsq(v);
	}

	float Vector::length() const
	{
		return cpvlength(v);
	}

	void Vector::normalize()
	{
		v = cpvnormalize(v);
	}

	float Vector::dot(const boost::shared_ptr<Vector> & v) const
	{
		return cpvdot(this->v, v->v);
	}

	float Vector::cross(const boost::shared_ptr<Vector> & v) const
	{
		return cpvcross(this->v, v->v);
	}

	float Vector::toAngle() const
	{
		return cpvtoangle(v);
	}

	boost::shared_ptr<Vector> Vector::perpendicular() const
	{
		pVector t(new Vector(cpvperp(v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::normalized() const
	{
		pVector t(new Vector(cpvnormalize(v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::project(const boost::shared_ptr<Vector> & v) const
	{
		pVector t(new Vector(cpvproject(this->v, v->v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::rotate(const boost::shared_ptr<Vector> & v) const
	{
		pVector t(new Vector(cpvrotate(this->v, v->v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::unrotate(const boost::shared_ptr<Vector> & v) const
	{
		pVector t(new Vector(cpvunrotate(this->v, v->v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::operator + (const boost::shared_ptr<Vector> & v) const
	{
		pVector t(new Vector(cpvadd(this->v, v->v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::operator - (const boost::shared_ptr<Vector> & v) const
	{
		pVector t(new Vector(cpvsub(this->v, v->v)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::operator * (float s) const
	{
		pVector t(new Vector(cpvmult(v, s)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::operator / (float s) const
	{
		if(s == 0)
			s = 1.0f;
		pVector t(new Vector(cpvmult(v, 1.0f/s)));
		return t;
	}

	boost::shared_ptr<Vector> Vector::operator - () const
	{
		pVector t(new Vector(cpvneg(v)));
		return t;
	}
 
	float Vector::getX() const
	{
		return v.x;
	}

	float Vector::getY() const
	{
		return v.y;
	}

	void Vector::setX(float x)
	{
		v.x = x;
	}

	void Vector::setY(float y)
	{
		v.y = y;
	}

	const char * Vector::toString() const
	{
		return cpvstr(v);
	}

} // love_chipmunk