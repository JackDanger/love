%{#include "Joint.h"%}

namespace love_chipmunk
{
	class Joint
	{
	public:		
	};
	
	typedef boost::shared_ptr<Joint> pJoint;
}

%template(SmartJoint) boost::shared_ptr<love_chipmunk::Joint>;
