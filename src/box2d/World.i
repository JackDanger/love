%{#include "World.h"%}

namespace love_box2d
{
	class World
	{
	public:
		void update(float dt);
	};
	
	typedef boost::shared_ptr<World> pWorld;
}

%template(SmartWorld) boost::shared_ptr<love_box2d::World>;
