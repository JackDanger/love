%{#include "PivotJoint.h"%}

namespace love_chipmunk
{
	class PivotJoint : public Joint
	{
	public:
	};
	
	typedef boost::shared_ptr<PivotJoint> pPivotJoint;
}

%template(SmartPivotJoint) boost::shared_ptr<love_chipmunk::PivotJoint>;
