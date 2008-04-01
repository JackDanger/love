#include "Space.h"

namespace love_chipmunk
{
	Space::Space()
	{
		space = cpSpaceNew();

		// @todo KILL ME (test code)

		cpBody * staticBody = cpBodyNew(INFINITY, INFINITY);


		{
			cpShape *seg = cpSegmentShapeNew(staticBody, cpv(0, 600), cpv(800, 600), 0.0f);
			seg->u = 1.0f; seg->e = 1.0f;
			cpSpaceAddStaticShape(space, seg);
		}

		{
			cpShape *seg = cpSegmentShapeNew(staticBody, cpv(0, 0), cpv(0, 600), 0.0f);
			seg->u = 1.0f; seg->e = 1.0f;
			cpSpaceAddStaticShape(space, seg);
		}


		{
			cpShape *seg = cpSegmentShapeNew(staticBody, cpv(800, 0), cpv(800, 600), 0.0f);
			seg->u = 1.0f; seg->e = 1.0f;
			cpSpaceAddStaticShape(space, seg);
		}

		
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

