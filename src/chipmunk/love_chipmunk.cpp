#include "love_chipmunk.h"

// From SWIG.
extern "C" {
	int luaopen_mod_chipmunk(lua_State * L);
}

namespace love_chipmunk
{
	bool DECLSPEC module_init(int argc, char ** argv, love::Core * core)
	{
		// Init chipmunk.
		cpInitChipmunk();
		return true;
	}

	bool DECLSPEC module_quit()
	{
		return true;
	}

	bool DECLSPEC module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
			luaopen_mod_chipmunk(s);
		return true;
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

	pShape newCircle(pSpace space, pBody body, float radius)
	{
		cpShape * shape = cpCircleShapeNew(body->get(), radius, cpvzero);
		shape->u = 1.0f;
		shape->e = 0.3f;

		pShape pshape(new Shape(space, shape));

		body->add(pshape);

		return pshape;
	}

} // love_chipmunk
