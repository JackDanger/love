%{#include "Joint.h"%}

namespace love_box2d
{
	class Joint
	{
	public:
	};
	
	typedef boost::shared_ptr<Joint> pJoint;
}

%template(SmartJoint) boost::shared_ptr<love_box2d::Joint>;
