/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
* 
* @author Anders Ruud
* @date 2008-07-05
*/

#ifndef LOVE_CHIPMUNK_VECTOR_H
#define LOVE_CHIPMUNK_VECTOR_H

// Chipmunk
#include "chipmunk/chipmunk.h"

// boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	/**
	* Chipmunk vector wrapper.
	**/
	class Vector
	{
		friend class Body;
		friend class BoundingBox;

	private:
		cpVect v;
	public:
		Vector();
		Vector(float a);
		Vector(float x, float y);
		Vector(cpVect v);
		float squaredLength() const;
		float length() const;
		void normalize();
		float dot(const boost::shared_ptr<Vector> & v) const;
		float cross(const boost::shared_ptr<Vector> & v) const;
		float toAngle() const;
		boost::shared_ptr<Vector> perpendicular() const;
		boost::shared_ptr<Vector> normalized() const;
		boost::shared_ptr<Vector> project(const boost::shared_ptr<Vector> & v) const;
		boost::shared_ptr<Vector> rotate(const boost::shared_ptr<Vector> & v) const;
		boost::shared_ptr<Vector> unrotate(const boost::shared_ptr<Vector> & v) const;
		boost::shared_ptr<Vector> operator + (const boost::shared_ptr<Vector> & v) const;
		boost::shared_ptr<Vector> operator - (const boost::shared_ptr<Vector> & v) const;
		boost::shared_ptr<Vector> operator * (float s) const;
		boost::shared_ptr<Vector> operator / (float s) const;
		boost::shared_ptr<Vector> operator - () const; 
		float getX() const;
		float getY() const;
		void setX(float x);
		void setY(float y);
		const char * toString() const;
	};

	typedef boost::shared_ptr<Vector> pVector;

} //love_chipmunk

#endif// LOVE_CHIPMUNK_VECTOR_H
