#include "love_chipmunk.h"

#include <limits.h>

// From SWIG.
extern "C" {
	int luaopen_mod_chipmunk(lua_State * L);
}

namespace love_chipmunk
{
	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.physics [" << "Chipmunk" << "]" << std::endl;
		// Init chipmunk.
		cpInitChipmunk();		
		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.physics [" << "Chipmunk" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
			luaopen_mod_chipmunk(s);
		return true;
	}

	int collision(cpShape * a, cpShape * b, cpContact * contacts, 
		int numContacts, cpFloat normal_coef, void *data)
	{
		static int number = 0;
		number++;
		std::cout << "Collision: " << number << std::endl;
		return 1;
	}

	pSpace newSpace()
	{
		pSpace space(new Space());
		return space;
	}

	pBody newBody(pSpace space, float x, float y, float m, float i)
	{
		pBody body(new Body(space, x, y, m, i));
		return body;
	}

	pShape newCircle(pBody body, float radius)
	{
		pShape shape(new DynamicCircleShape(body, radius));
		body->addShape(shape);
		return shape;
	}

	pSegmentShape newSegment(pBody body, float x1, float y1, float x2, float y2)
	{
		pSegmentShape shape(new DynamicSegmentShape(body, x1, y1, x2, y2));
		body->addShape(shape);
		return shape;
	}

	float infinity()
	{
		return INFINITY;
	}

	

} // love_chipmunk
