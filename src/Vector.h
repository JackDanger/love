/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

// LOVE
#include "Matrix.h"

// STD
#include <cmath>



#ifndef LOVE_VECTOR_H
#define LOVE_VECTOR_H

namespace love 
{



	/**
	* 2D Vector class.
	* 
	* @author Anders Ruud
	* @date 2006-05-13
	**/
	class Vector
	{
	private:

		// The components.
		float x, y;

	public:

		/**
		* @brief Creates a new (1,1) Vector.
		**/
		Vector();

		/**
		* @brief Creates a new Vector.
		* @param x The x position/dimension.
		* @param y The y position/dimension.
		**/
		Vector(float x, float y);

		/**
		* @brief Gets the length of the Vector.
		* @return The length of the Vector.
		*
		* This method requires sqrt() and should be used
		* carefully. 
		**/
		float getLength() const;

		/**
		* @brief Normalizes the Vector.
		* @return The old length of the Vector.
		**/
		float normalize();

		/**
		* @brief Gets a normal to the Vector.
		* @return A normal to the Vector.
		**/

		Vector getNormal() const;

		/**
		* Operator overloads
		**/

		/**
		* @brief Adds a Vector to this Vector.
		* @param v The Vector we want to add to this Vector.
		* @return The resulting Vector.
		**/
		Vector operator + (const Vector & v) const;

		/**
		* @brief Substracts a Vector to this Vector.
		* @param v The Vector we want to subtract to this Vector.
		* @return The resulting Vector.
		**/
		Vector operator - (const Vector & v) const;

		/**
		* @brief Resizes a Vector by a scalar.
		* @param s The scalar with which to resize the Vector.
		* @return The resulting Vector.
		**/
		Vector operator * (float s) const;

		/**
		* @brief Resizes a Vector by a scalar.
		* @param s The scalar with which to resize the Vector.
		* @return The resulting Vector.
		**/
		Vector operator / (float s) const;

		/**
		* @brief Reverses the Vector.
		* @return The reversed Vector.
		**/
		Vector operator - () const; 

		/**
		* @brief Adds a Vector to this Vector, and also saves changes in the first Vector.
		* @param v The Vector we want to add to this Vector.
		**/
		void operator += (const Vector & v);

		/**
		* @brief Subtracts a Vector to this Vector, and also saves changes in the first Vector.
		* @param v The Vector we want to subtract to this Vector.
		**/
		void operator -= (const Vector & v);

		/**
		* @brief Resizes the Vector, and also saves changes in the first Vector.
		* @param s The scalar by which we want to resize the Vector.
		**/
		void operator *= (float s);

		/**
		* @brief Resizes the Vector, and also saves changes in the first Vector.
		* @param s The scalar by which we want to resize the Vector.
		**/
		void operator /= (float s);

		/**
		* @brief Calculates the dot product of two Vectors.
		* @return The dot product of the two Vectors.
		**/
		float operator * (const Vector & v) const;

		/**
		* @brief Applies a transformation Matrix to the Vector.
		* @param m The Matrix to use for the transformation.
		* @return The resulting Vector of the transformation.
		**/
		Vector operator * (const Matrix & m) const;

		/**
		* @brief Applies a transpose transformation Matrix to the Vector.
		* @param m The Matrix to use for the transformation.
		* @return The resulting Vector of the transformation.
		**/
		Vector operator ^ (const Matrix & m) const;

		/**
		* @brief Applies a transformation Matrix to the Vector (and stores the change).
		* @param m The Matrix to use for the transformation.
		**/
		inline void operator *= (const Matrix & m);

		/**
		* @brief Calculates the cross product of two Vectors.
		* @return The cross product of the two Vectors.
		**/
		float operator ^ (const Vector & v) const;

		bool operator == (const Vector & v) const;

		bool operator < (const Vector & v) const;
		/**
		* @brief Gets the x value of the Vector.
		* @return The x value of the Vector.
		**/
		float getX() const;
		
		/**
		* @brief Gets the x value of the Vector.
		* @return The x value of the Vector.
		**/
		float getY() const;

		/**
		* @brief Sets the x value of the Vector.
		* @param The x value of the Vector.
		**/
		void setX(float x);

		/**
		* @brief Sets the x value of the Vector.
		* @param The x value of the Vector.
		**/
		void setY(float y);




	};


	inline float Vector::getLength() const
	{
		return sqrt(x*x + y*y);
	}

	inline Vector Vector::getNormal() const 
	{
		return Vector(-y, x);
	}

	inline float Vector::normalize()
	{
		
		float len = getLength();

		if(len > 0)
			(*this) /= len;

		return len;
	}

	/**
	* Inline methods must have body in header.
	**/

	inline Vector::Vector() : x(0.0f), y(0.0f)
	{
	}

	inline Vector::Vector(float x, float y) : x(x), y(y)
	{
	}

	inline Vector Vector::operator + (const Vector & v) const
	{
		return Vector(x + v.getX(), y + v.getY());
	}

	inline Vector Vector::operator - (const Vector & v) const
	{
		return Vector(x - v.getX(), y - v.getY());
	}
	
	inline Vector Vector::operator * (float s) const
	{
		return Vector(x*s, y*s);
	}

	inline Vector Vector::operator / (float s) const
	{
		return Vector(x/s, y/s);
	}

	inline Vector Vector::operator - () const
	{
		return Vector(-x, -y);
	}

	inline void Vector::operator += (const Vector & v) 
	{
		x += v.getX();
		y += v.getY();
	}

	inline void Vector::operator -= (const Vector & v) 
	{
		x -= v.getX();
		y -= v.getY();
	}

	inline void Vector::operator *= (float s)
	{
		x *= s;
		y *= s;
	}

	inline void Vector::operator /= (float s)
	{
		x /= s;
		y /= s;
	}

	inline float Vector::operator * (const Vector & v) const
	{
		return x * v.getX() + y * v.getY();
	}

	inline Vector Vector::operator * (const Matrix & m) const
	{
		return Vector((m.get0()*x + m.get2()*y), (m.get1()*x + m.get3()*y));
	}

	inline Vector Vector::operator ^ (const Matrix & m) const
	{
		return Vector((m.get0()*x + m.get1()*y), (m.get2()*x + m.get3()*y));
	}

	inline void Vector::operator *= (const Matrix & m)
	{
		x *= m.get0(); x += (m.get2()*y);
		y *= m.get3(); y += (m.get1()*x);
	}

	inline float Vector::operator ^ (const Vector & v) const
	{
		return x * v.getY() - y * v.getX();
	}


	inline bool Vector::operator == (const Vector & v) const
	{
		return getLength() == v.getLength();
	}

	inline bool Vector::operator < (const Vector & v) const
	{
		return getLength() < v.getLength();
	}
	/**
	* Accessor methods
	**/

	inline float Vector::getX() const
	{
		return x;
	}

	inline float Vector::getY() const
	{
		return y;
	}

	inline void Vector::setX(float x)
	{
		this->x = x;
	}

	inline void Vector::setY(float y)
	{
		this->y = y;
	}

} //love

#endif// LOVE_VECTOR_H
