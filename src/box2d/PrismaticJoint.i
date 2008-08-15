%{#include "PrismaticJoint.h"%}

namespace love_box2d
{
	class PrismaticJoint
	{
	public:
		float getTranslation() const;
		float getSpeed() const;

		void setMotorEnabled(bool motor);
		bool isMotorEnabled() const;
		void setMaxMotorForce(float force);
		float getMaxMotorForce() const;
		void setMotorSpeed(float speed);
		float getMotorSpeed() const;
		float getMotorForce() const;

		void setLimitsEnabled(bool limit);
		bool isLimitsEnabled() const;
		void setUpperLimit(float limit);
		void setLowerLimit(float limit);
		void setLimits(float lower, float upper);
		float getLowerLimit() const;
		float getUpperLimit() const;
	};
	
	typedef boost::shared_ptr<PrismaticJoint> pPrismaticJoint;
}

%template(SmartPrismaticJoint) boost::shared_ptr<love_box2d::PrismaticJoint>;
