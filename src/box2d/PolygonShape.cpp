#include "PolygonShape.h"

// Module
#include "Body.h"

namespace love_box2d
{
	PolygonShape::PolygonShape(boost::shared_ptr<Body> body, b2PolygonDef * def)
		: Shape(body)
	{
		shape = body->body->CreateShape(def);
		shape->SetUserData((void*)data);
	}

	PolygonShape::~PolygonShape()
	{
		body->body->DestroyShape(shape);
		shape = 0;
	}

	int PolygonShape::getPoints(lua_State * L)
	{
		love::luax_assert_argc(L, 0);
		b2PolygonShape * p = (b2PolygonShape *)shape;
		const b2Vec2 * vertices = p->GetVertices();
		int count = p->GetVertexCount();
		for(int i = 0;i<count; i++)
		{
			b2Vec2 v = body->body->GetWorldPoint(vertices[i]);
			lua_pushnumber(L, v.x);
			lua_pushnumber(L, v.y);
		}
		return count*2;
	}

} // love_box2d