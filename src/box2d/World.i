%{#include "World.h"%}

namespace love_box2d
{
	class World
	{
	public:
		void update(float dt);
		void setGravity(float x, float y);
		int getBodyCount();
		int getJointCount();
	};
	
	typedef boost::shared_ptr<World> pWorld;
}

%template(SmartWorld) boost::shared_ptr<love_box2d::World>;
