%{#include "SlideJoint.h"%}

namespace love_chipmunk
{
	class SlideJoint : public Joint
	{
	public:
	};
	
	typedef boost::shared_ptr<SlideJoint> pSlideJoint;
}

%template(SmartSlideJoint) boost::shared_ptr<love_chipmunk::SlideJoint>;
