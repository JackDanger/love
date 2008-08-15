%{#include "RevoluteJoint.h"%}

namespace love_box2d
{
	class RevoluteJoint
	{
	public:
		float getAngle() const;
		float getSpeed() const;

		void setMotorEnabled(bool motor);
		bool isMotorEnabled() const;
		void setMaxMotorTorque(float torque);
		float getMaxMotorTorque() const;
		void setMotorSpeed(float speed);
		float getMotorSpeed() const;
		float getMotorTorque() const;

		void setLimitsEnabled(bool limit);
		bool isLimitsEnabled() const;
		void setUpperLimit(float limit);
		void setLowerLimit(float limit);
		void setLimits(float lower, float upper);
		float getLowerLimit() const;
		float getUpperLimit() const;
	};
	
	typedef boost::shared_ptr<RevoluteJoint> pRevoluteJoint;
}

%template(SmartRevoluteJoint) boost::shared_ptr<love_box2d::RevoluteJoint>;
