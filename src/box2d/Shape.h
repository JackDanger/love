/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_BOX2D_SHAPE_H
#define LOVE_BOX2D_SHAPE_H

// LOVE
#include <love/mod.h>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

namespace love_box2d
{
	class Body;

	struct shapeudata
	{
		love::pReference ref;
	};

	class Shape
	{
	protected:
		boost::shared_ptr<Body> body;
		b2Shape * shape;
		shapeudata * data;
	public:
		Shape(boost::shared_ptr<Body> body);
		virtual ~Shape();

		int getType() const;

		void setFriction(float friction);
		void setRestitution(float restitution);
		void setDensity(float density);
		void setSensor(bool sensor);

		float getFriction() const;
		float getRestituion() const;
		float getDensity() const;
		bool isSensor() const;

		boost::shared_ptr<Body> getBody() const;
		bool testPoint(float x, float y) const;

		void setCategoryBits(int bits);
		int getCategoryBits() const;

		void setMaskBits(int bits);
		int getMaskBits() const;

		int setCategory(lua_State * L);
		int getCategory(lua_State * L);

		int setMask(lua_State * L);
		int getMask(lua_State * L);

		int setData(lua_State * L);
		int getData(lua_State * L);

		int getBoundingBox(lua_State * L);

	private:
		uint16 getBits(lua_State * L);
		int pushBits(lua_State * L, uint16 bits);
	};

	typedef boost::shared_ptr<Shape> pShape;

} // love_box2d

#endif // LOVE_BOX2D_SHAPE_H
