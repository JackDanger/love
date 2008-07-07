%{#include "Vector.h"%}

namespace love_chipmunk
{
	class Vector
	{
	public:
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
}

%template(SmartVector) boost::shared_ptr<love_chipmunk::Vector>;
