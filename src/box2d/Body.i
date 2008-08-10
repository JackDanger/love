%{#include "Body.h"%}

namespace love_box2d
{
	class Body
	{
	public:
	
		float getX();
		float getY();
		float getAngle();
		
		void applyImpulse(float jx, float jy);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy, float rx, float ry);
		
		void setX(float x);
		void setY(float y);
		void setPosition(float x, float y);
		void setMassFromShapes();
	};
	
	typedef boost::shared_ptr<Body> pBody;
}

%template(SmartBody) boost::shared_ptr<love_box2d::Body>;
