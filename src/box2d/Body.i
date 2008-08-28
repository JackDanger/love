%{#include "Body.h"%}

namespace love_box2d
{
	class Body
	{
	public:
	
		float getX();
		float getY();
		
		float getAngle();
		float getSpin() const;
		
		float getMass() const;
		float getInertia() const;
		
		float getAngularDamping() const;
		float getDamping() const;

		void applyImpulse(float jx, float jy);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy);
		void applyForce(float fx, float fy, float rx, float ry);
		void applyTorque(float t);
	
		void setX(float x);
		void setY(float y);
		void setPosition(float x, float y);
		void setVelocity(float x, float y);
		
		void setAngle(float d);
		void setSpin(float r);
		
		void setMassFromShapes();
		void setMass(float x, float y, float m, float i);
		
		void setAngularDamping(float d);
		void setDamping(float d);

		bool isBullet() const;
		void setBullet(bool bullet);
		bool isStatic() const;
		bool isDynamic() const;
		bool isFrozen() const;
		bool isSleeping() const;

		void setAllowSleep(bool allow);
		void setSleep(bool sleep);
	};
	
	typedef boost::shared_ptr<Body> pBody;
}

%template(SmartBody) boost::shared_ptr<love_box2d::Body>;
