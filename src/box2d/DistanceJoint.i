%{#include "DistanceJoint.h"%}

namespace love_box2d
{
	class DistanceJoint
	{
	public:
		void setLength(float length);
		float getLength() const;
		void setFrequency(float hz);
		float getFrequency() const;
		void setDamping(float d);
		float getDamping() const;
	};
	
	typedef boost::shared_ptr<DistanceJoint> pDistanceJoint;
}

%template(SmartDistanceJoint) boost::shared_ptr<love_box2d::DistanceJoint>;
