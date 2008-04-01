#include "love_chipmunk.h"

// From SWIG.
extern "C" {
	int luaopen_mod_chipmunk(lua_State * L);
}

namespace love_chipmunk
{
	bool init(love_mod::modconf * conf)
	{
		// Init chipmunk.
		cpInitChipmunk();

		love_mod::setConf(conf);
		love_mod::report_init("love.physics", "Chipmunk");
		return true;
	}

	bool quit()
	{
		love_mod::report_init("love.physics", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_chipmunk(s);
		love_mod::do_string("love.physics = mod_chipmunk");
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
