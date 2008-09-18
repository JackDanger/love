#include "Shape.h"

// Module
#include "Body.h"

// STD
#include <bitset>

namespace love_box2d
{
	Shape::Shape(boost::shared_ptr<Body> body)
		: body(body)
	{
		data = new shapeudata();
	}

	Shape::~Shape()
	{
		delete data;
		data = 0;
	}

	int Shape::getType() const
	{
		switch(shape->GetType())
		{
		case e_circleShape:
			return love::SHAPE_CIRCLE;
		case e_polygonShape:
			return love::SHAPE_POLYGON;
		default:
			return -1;
		}
	}

	void Shape::setFriction(float friction)
	{
		shape->m_friction = friction;
	}

	void Shape::setRestitution(float restitution)
	{
		shape->m_restitution = restitution;
	}

	void Shape::setDensity(float density)
	{
		shape->m_density = density;
	}

	void Shape::setSensor(bool sensor)
	{
		shape->m_isSensor = sensor;
	}

	float Shape::getFriction() const
	{
		return shape->GetFriction();
	}

	float Shape::getRestituion() const
	{
		return shape->GetRestitution();
	}

	float Shape::getDensity() const
	{
		return shape->m_density;
	}

	bool Shape::isSensor() const
	{
		return shape->IsSensor();
	}

	boost::shared_ptr<Body> Shape::getBody() const
	{
		return body;
	}

	bool Shape::testPoint(float x, float y) const
	{
		return shape->TestPoint(shape->GetBody()->GetXForm(), b2Vec2(x, y));
	}

	int Shape::testSegment(lua_State * L)
	{
		love::luax_assert_argc(L, 4, 4);

		b2Segment s;

		s.p1.x = (float)lua_tonumber(L, 1);
		s.p1.y = (float)lua_tonumber(L, 2);
		s.p2.x = (float)lua_tonumber(L, 3);
		s.p2.y = (float)lua_tonumber(L, 4);

		float lambda;
		b2Vec2 normal;
		
		if(shape->TestSegment(shape->GetBody()->GetXForm(), &lambda, &normal, s, 1.0f))
		{
			lua_pushnumber(L, lambda);
			lua_pushnumber(L, normal.x);
			lua_pushnumber(L, normal.y);
			return 3;
		}

		return 0;
	}

	void Shape::setCategoryBits(int bits)
	{
		b2FilterData f = shape->GetFilterData();
		f.categoryBits = (uint16)bits;
		shape->SetFilterData(f);
		shape->GetBody()->GetWorld()->Refilter(shape);
	}

	int Shape::getCategoryBits() const
	{
		return shape->GetFilterData().categoryBits;
	}

	void Shape::setMaskBits(int bits)
	{
		b2FilterData f = shape->GetFilterData();
		f.maskBits = (uint16)bits;
		shape->SetFilterData(f);
		shape->GetBody()->GetWorld()->Refilter(shape);
	}

	int Shape::getMaskBits() const
	{
		return shape->GetFilterData().maskBits;
	}

	int Shape::setCategory(lua_State * L)
	{
		setCategoryBits(getBits(L));
		return 0;
	}

	int Shape::getCategory(lua_State * L)
	{
		return pushBits(L, shape->GetFilterData().categoryBits);
	}

	int Shape::setMask(lua_State * L)
	{
		setMaskBits(~getBits(L));
		return 0;
	}

	int Shape::getMask(lua_State * L)
	{
		return pushBits(L, ~(shape->GetFilterData().maskBits));
	}

	int Shape::setData(lua_State * L)
	{
		love::luax_assert_argc(L, 1, 1);
		data->ref.reset<love::Reference>(new love::Reference(L));
		return 0;
	}

	int Shape::getData(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		if(data->ref != 0)
			data->ref->push();
		else
			lua_pushnil(L);

		return 1;
	}

	int Shape::getBoundingBox(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		b2AABB bb;
		shape->ComputeAABB(&bb, shape->GetBody()->GetXForm());

		// Top left.
		lua_pushnumber(L, bb.lowerBound.x);
		lua_pushnumber(L, bb.upperBound.y);

		// Bottom left.
		lua_pushnumber(L, bb.lowerBound.x);
		lua_pushnumber(L, bb.lowerBound.y);

		// Bottom right.
		lua_pushnumber(L, bb.upperBound.x);
		lua_pushnumber(L, bb.lowerBound.y);

		// Top right.
		lua_pushnumber(L, bb.upperBound.x);
		lua_pushnumber(L, bb.upperBound.y);

		return 8;
	}

	uint16 Shape::getBits(lua_State * L)
	{
		// Get number of args.
		int argc = lua_gettop(L);

		// The new bitset.
		std::bitset<16> b;

		for(int i = 1;i<=argc;i++)
		{
			size_t bpos = (size_t)(lua_tointeger(L, i)-1);
			if(bpos < 0 || bpos > 16) 
				return luaL_error(L, "Values must be in rage 1-16.");
			b.set(bpos, true);
		}
		
		return (uint16)b.to_ulong();
	}

	int Shape::pushBits(lua_State * L, uint16 bits)
	{
		// Create a bitset.
		std::bitset<16> b((unsigned long)bits);

		// Push all set bits.
		for(int i = 0;i<16;i++)
			if(b.test(i))
				lua_pushinteger(L, i+1);

		// Count number of set bits.
		return (int)b.count();
	}

} // love_box2d
