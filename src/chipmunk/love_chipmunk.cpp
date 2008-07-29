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
			luaopen_mod_chipmunk(s);
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

	pCircleShape newCircle(pBody body, float radius, float x, float y)
	{
		pCircleShape shape(new CircleShape(body, radius, x, y));
		body->addShape(shape);
		return shape;
	}

	pSegmentShape newSegment(pBody body, float x1, float y1, float x2, float y2)
	{
		pSegmentShape shape(new SegmentShape(body, cpv(x1, y1), cpv(x2, y2)));
		body->addShape(shape);
		return shape;
	}

	pPinJoint newPin(pBody body1, pBody body2, float x1, float y1, float x2, float y2)
	{
		pPinJoint j(new PinJoint(body1, body2, cpv(x1, y1), cpv(x2, y2)));
		body1->addJoint(j);
		body2->addJoint(j);
		return j;
	}

	pSlideJoint newSlide(pBody body1, pBody body2, float x1, float y1, float x2, float y2, float min, float max)
	{
		pSlideJoint j(new SlideJoint(body1, body2, cpv(x1,y1), cpv(x2, y2), min, max));
		body1->addJoint(j);
		body2->addJoint(j);
		return j;
	}

	pPivotJoint newPivot(pBody body1, pBody body2, float x, float y)
	{
		pPivotJoint j(new PivotJoint(body1, body2, cpv(x,y)));
		body1->addJoint(j);
		body2->addJoint(j);
		return j;
	}

	pGrooveJoint newGroove(pBody body1, pBody body2, float x1, float y1, float x2, float y2, float x3, float y3)
	{
		pGrooveJoint j(new GrooveJoint(body1, body2, cpv(x1,y1), cpv(x2, y2), cpv(x3, y3)));
		body1->addJoint(j);
		body2->addJoint(j);
		return j;
	}

	int newPolygon(lua_State * L)
	{
		int n = lua_gettop(L);
		if( n != 2 ) return luaL_error(L, "Function requires two parameters.");

		// First one should be a body.
		pBody body = mod_to_body(L, 1);

		// Second one should be table.
		if( !lua_istable(L, 2) ) return luaL_error(L, "Error, second argument must be a table.");

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

		// Create the polygon.
		pPolygonShape poly(new PolygonShape(body, (cpVect*)verts, (int)(num/2)));
		
		mod_push_polygonshape(L, poly);

		return 1;
	}

} // love_chipmunk
