#include "love_chipmunk.h"
#include "mod_chipmunk.h"

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
			mod_open(s);
		return true;
	}

	int collision(cpShape * a, cpShape * b, cpContact * contacts, 
		int numContacts, cpFloat normal_coef, void *data)
	{
		static int number = 0;
		number++;
		//std::cout << "Collision: " << number << std::endl;
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

	pBody newStaticBody(pSpace space, float x, float y, float m, float i)
	{
		pBody body(new Body(space, x, y, INFINITY, INFINITY, false));
		return body;
	}

	pShape newCircle(pBody body, float radius)
	{
		pShape shape(new CircleShape(body, radius));
		body->addShape(shape);
		return shape;
	}

	pSegmentShape newSegment(pBody body, float x1, float y1, float x2, float y2)
	{
		pSegmentShape shape(new SegmentShape(body, cpv(x1, y1), cpv(x2, y2)));
		body->addShape(shape);
		return shape;
	}

	/**
	int newPolygon(lua_State * L)
	{
		int n = lua_gettop(L);
		if( n != 2 ) return luaL_error(L, "Function requires a two parameters.");

		// First one should be a body.
		pBody body = mod_chipmunk_swig_get_body(L);

		// Second one should be table.
		if( !lua_istable(L, -1) ) return luaL_error(L, "Error, second argument must be a table.");

		// Get the size of that table.
		int num = (int)lua_objlen(L, -1);

		if(num < 6) return luaL_error(L, "Error, need at least 6 vertices.");
		if((num % 2) != 0) return luaL_error(L, "Error, number of vertices must be multiple of 2.");

		// Allocate data for the vertices.
		float * verts = new float[num];
		int pos = 0;

		// Traverse it.
		lua_pushnil(L); 
		while (lua_next(L, -2) != 0) {
			verts[pos] = (float)lua_tonumber(L, -1);
			pos++;
			lua_pop(L, 1); // Remove value, keep key for next iteration.
		}

		lua_pop(L, 2);

		// Create the polygon.
		pPolygonShape poly(new PolygonShape(body, (cpVect*)verts, (int)(num/2)));

		mod_chipmunk_push_polygon(L, poly);

		std::cout << "Stack size: " << lua_gettop(L) << std::endl;

		return 1;
	}
	**/

} // love_chipmunk
