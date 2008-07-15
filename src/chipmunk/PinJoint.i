%{#include "PinJoint.h"%}

namespace love_chipmunk
{
	class PinJoint : public Joint
	{
	public:
	};
	
	typedef boost::shared_ptr<PinJoint> pPinJoint;
}

%template(SmartPinJoint) boost::shared_ptr<love_chipmunk::PinJoint>;
