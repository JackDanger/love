%{#include "DistanceJoint.h"%}

namespace love_box2d
{
	class DistanceJoint
	{
	public:
	};
	
	typedef boost::shared_ptr<DistanceJoint> pDistanceJoint;
}

%template(SmartDistanceJoint) boost::shared_ptr<love_box2d::DistanceJoint>;
