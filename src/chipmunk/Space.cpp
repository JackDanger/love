#include "Space.h"

namespace love_chipmunk
{

extern int collision(cpShape * a, cpShape * b, cpContact * contacts, 
		int numContacts, cpFloat normal_coef, void *data);

	Space::Space()
	{
		space = cpSpaceNew();
		//cpSpaceAddCollisionPairFunc(space, 1, 2, collision, 0);	
	}

	Space::~Space()
	{
		cpSpaceFree(space);
	}

	void Space::update(float dt)
	{
		cpSpaceStep(space, dt);
	}

	void Space::setGravity(float x, float y)
	{
		space->gravity = cpv(x, y);
	}

	void Space::setGravity(float y)
	{
		space->gravity = cpv(0, y);
	}

	void Space::setDamping(float d)
	{
		space->damping = d;
	}

	void Space::resizeStaticHash(float dim, int count)
	{
		cpSpaceResizeStaticHash(space, dim, count);
	}

	void Space::resizeActiveHash(float dim, int count)
	{
		cpSpaceResizeActiveHash(space, dim, count);
	}

} // love_chipmunk

