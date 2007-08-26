#ifndef LOVE_PHYSICAL_H
#define LOVE_PHYSICAL_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Physical
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-08-27
	* @brief Contains variables related to physics.
	**/
	class Physical 
	{
	private:

		float friction;
		float restitution;
		float glue;

		float mass;
		float inverseMass; // 1/mass

		static float VERY_SMALL;

	public:
	
		Physical();
		~Physical();

		bool isMovable();

		float getFriction();
		void setFriction(float friction);

		float getRestitution();
		void setRestitution(float restitution);

		float getGlue();
		void setGlue(float glue);

		float getMass();
		void setMass(float mass);

		float getInverseMass();
	};

	typedef boost::shared_ptr<Physical> pPhysical;
}

#endif
