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
	// Forward declarations.
	class Body;

	/**
	* This struct is stored in a void pointer
	* in the Box2D Shape class. For now, all we
	* need is a Lua reference to arbitrary data,
	* but we might need more later.
	**/
	struct shapeudata
	{
		// Reference to arbitrary data.
		love::pReference ref;
	};

	/**
	* A Shape is geometry attached to a Body.
	* A Body has position and orientation, and 
	* a Shape's geometry will be affected by the parent
	* body's transformation.
	**/
	class Shape
	{
	protected:
		
		// A shared_ptr to the parent Body. If the Body
		// is destroyed, all child shapes are destroyed as well. 
		// This ensures that all child shapes are always destroyed
		// *before* the parent Body.
		boost::shared_ptr<Body> body;

		// The Box2D shape.
		b2Shape * shape;

		// Our shape data, to be stored in
		// the Box2D shape.
		shapeudata * data;

	public:

		/**
		* Creates a Shape attatched to the specified
		* Body. 
		**/
		Shape(boost::shared_ptr<Body> body);

		virtual ~Shape();

		/**
		* Gets the type of Shape. Useful for 
		* debug drawing.
		**/
		int getType() const;

		/**
		* Sets the friction of the Shape.
		* @param friction The new friction.
		**/
		void setFriction(float friction);

		/**
		* Sets the restitution for the Shape.
		* @param restitution The restitution.
		**/
		void setRestitution(float restitution);

		/**
		* Sets the density of the Shape.
		* @param density The density of the Shape.
		**/
		void setDensity(float density);

		/**
		* Set whether this shape should be a sensor or not.
		* @param sensor True if sensor, false if not.
		**/
		void setSensor(bool sensor);

		/**
		* Gets the friction of the Shape.
		* @returns The friction.
		**/
		float getFriction() const;

		/**
		* Gets the restitution of the Shape.
		* @return The restitution of the Shape.
		**/
		float getRestituion() const;

		/**
		* Gets the density of the Shape.
		* @return The density.
		**/
		float getDensity() const;

		/**
		* Checks whether this Shape acts as a sensor.
		* @return True if sensor, false otherwise.
		**/
		bool isSensor() const;

		/**
		* Get the body attatched to this Shape.
		* @return The parent Body.
		**/
		boost::shared_ptr<Body> getBody() const;

		/**
		* Checks if a point is inside the Shape.
		* @param x The x-component of the Shape.
		* @param y The y-component of the Shape.
		**/
		bool testPoint(float x, float y) const;

		/**
		* Tests whether a line segment intersects a Shape.
		**/
		int testSegment(lua_State * L);

		/**
		* Sets the category bits of a Shape. This is
		* way faster than setCategory.
		* @param bits A 16-bits integer representing the categories.
		**/
		void setCategoryBits(int bits);

		/**
		* Gets the category bits of the Shape.
		* @return A 16-bits integer representing the categories.
		**/
		int getCategoryBits() const;

		/**
		* Set the mask bits of the Shape.
		* @param bits A 16-bits integer representing
		* the categories that should be masked.
		**/
		void setMaskBits(int bits);

		/**
		* Gets the current mask bits.
		* @return A 16-bit integer representing the current
		* masks categories.
		**/
		int getMaskBits() const;

		/**
		* With this function, you can easily set the categories
		* a Shape is a member of.
		* 
		* The function accepts 1-16 arguments. Each argument must 
		* be a number from 1-16, and must be unique in the list.
		**/
		int setCategory(lua_State * L);

		/**
		* Returns the categories this Shape is
		* a member of. So if the Shape is a member
		* of 5 categories, this function returns five
		* values.
		**/ 
		int getCategory(lua_State * L);

		/**
		* Sets which categories this Shape should *not*
		* collide with. 
		* 
		* The function works the same was as setCategory, but
		* each entry here represents a 0 in the bit string, not
		* a 1 like setCategory.
		**/
		int setMask(lua_State * L);

		/**
		* Returns the current masked categories.
		* If there are 5 masked categories, then this
		* function will have 5 return values.
		**/
		int getMask(lua_State * L);

		/**
		* This function stores an in-C reference to
		* arbitrary Lua data in the Box2D shape object.
		* 
		* The data set here will be passed to the collision
		* handler when collisions occur.
		**/
		int setData(lua_State * L);

		/**
		* Gets the data set with setData. If no
		* data is set, nil is returned.
		**/
		int getData(lua_State * L);

		/**
		* Gets the bounding box for this Shape. 
		* The function returns eight values which can be
		* passed directly to love.graphics.polygon.
		**/ 
		int getBoundingBox(lua_State * L);

	private:

		/**
		* Gets a 16-integer from the current stack top.
		* @param The 16-bit integer.
		**/
		uint16 getBits(lua_State * L);

		/**
		* Push each set bit in a 16-bit integer as
		* a list of integer indices. That is, if the bits are 
		* set to 0000 0000 0011 0001, then this function will
		* push (1, 5, 6) on the stack.
		**/
		int pushBits(lua_State * L, uint16 bits);
	};

	typedef boost::shared_ptr<Shape> pShape;

} // love_box2d

#endif // LOVE_BOX2D_SHAPE_H
