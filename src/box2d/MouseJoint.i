%{#include "MouseJoint.h"%}

namespace love_box2d
{
	class MouseJoint
	{
	public:
		void setTarget(float x, float y);
	};
	
	typedef boost::shared_ptr<MouseJoint> pMouseJoint;
}

%template(SmartMouseJoint) boost::shared_ptr<love_box2d::MouseJoint>;
