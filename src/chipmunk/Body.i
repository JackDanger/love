%{#include "Body.h"%}

namespace love_chipmunk
{
	class Body
	{
	public:
		float getX();
		float getY();
		float getAngle();

		void setMass(float m);
		void setMoment(float m);
		void setAngle(float a);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy, float rx, float ry);
		void resetForces();	
	};
	
	typedef boost::shared_ptr<Body> pBody;
}

%template(SmartBody) boost::shared_ptr<love_chipmunk::Body>;
