%{#include "GrooveJoint.h"%}

namespace love_chipmunk
{
	class GrooveJoint : public Joint
	{
	public:
	};
	
	typedef boost::shared_ptr<GrooveJoint> pGrooveJoint;
}

%template(SmartGrooveJoint) boost::shared_ptr<love_chipmunk::GrooveJoint>;
