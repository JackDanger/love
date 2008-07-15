#include "PolygonShape.h"

#include "Body.h"

#include "love_chipmunk.h"
#include "mod_chipmunk.h"

namespace love_chipmunk
{
	PolygonShape::PolygonShape(boost::shared_ptr<Body> body, cpVect * verts, int num)
		: Shape(body), verts(verts)
	{
		polygonShape = cpPolyShapeAlloc();
		cpPolyShapeInit(polygonShape, body->body, num, verts, cpvzero);
		shape = (cpShape*)polygonShape;
		shape->e = 0.5f;
		shape->u = 0.5f;

		if(body->isDynamic())
			cpSpaceAddShape(body->space->space, shape);
		else
			cpSpaceAddStaticShape(body->space->space, shape);	
	}

	PolygonShape::~PolygonShape()
	{
		if(verts != 0)
		{
			verts = 0;
			delete [] verts;
		}

		if(body->isDynamic())
			cpSpaceRemoveShape(body->space->space, (cpShape*)polygonShape);
		else
			cpSpaceRemoveStaticShape(body->space->space, (cpShape*)polygonShape);

		cpShapeFree((cpShape*)polygonShape);
		polygonShape = 0;
	}

	int _PolygonShape_getTransformedPoints(lua_State * L)
	{
		// Check that the number of arguments is correct.
		if(lua_gettop(L) != 1) 
			return luaL_error(L, "Error, function does not take any arguments.");

		// Get the PolygonShape.
		pPolygonShape poly = mod_to_polygonshape(L, 1);

		// Get the number of vertices.
		int n = poly->polygonShape->numVerts;

		// Create a new table.
		lua_createtable(L, n*2, 0);

		for(int i = 0;i<n;i++)
		{
			lua_pushnumber(L, poly->polygonShape->tVerts[i].x);
			lua_rawseti(L, -2, i*2+1);
			lua_pushnumber(L, poly->polygonShape->tVerts[i].y);
			lua_rawseti(L, -2, i*2+2);
		}

		// Return the table.
		return 1;
	}

} // love_chipmunk

