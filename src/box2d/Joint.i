%{#include "Joint.h"%}

namespace love_box2d
{
	class Joint
	{
	public:
		int getType() const;
		float getReactionTorque();
		void setCollideConnected(bool collide);
		bool getCollideConnected() const;
	};
	
	typedef boost::shared_ptr<Joint> pJoint;
}

%template(SmartJoint) boost::shared_ptr<love_box2d::Joint>;
