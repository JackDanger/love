/**
* @file Vextor.h
* @brief Contains definition of class Vextor.
* @date 2006-05-13
* @author Anders Ruud
**/

#include <cmath>
#include "Matrix.h"

// boost
#include <boost/shared_ptr.hpp>


#ifndef LOVE_VEXTOR_H
#define LOVE_VEXTOR_H

namespace love 
{



	/**
	* @class Vextor
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-05-13
	* @brief A Vextor is an mathematical entity which posesses the attributes 
	* of a Point and a Vector.
	**/
	class Vextor
	{
	private:

		// The position/size of the Vextor.
		float x;
		float y;

	public:

		/**
		* @brief Creates a new (1,1) Vextor.
		**/
		Vextor();

		/**
		* @brief Creates a new Vextor.
		* @param x The x position/dimension.
		* @param y The y position/dimension.
		**/
		Vextor(float x, float y);

		~Vextor();

		/**
		* @brief Gets the length of the Vextor.
		* @return The length of the Vextor.
		*
		* This method requires sqrt() and should be used
		* carefully. 
		**/
		float getLength() const;

		/**
		* @brief Normalizes the Vextor.
		* @return The old length of the Vextor.
		**/
		float normalize();

		/**
		* @brief Gets a normal to the Vextor.
		* @return A normal to the Vextor.
		**/

		Vextor getNormal() const;

		/**
		* Operator overloads
		**/

		/**
		* @brief Adds a Vextor to this Vextor.
		* @param v The Vextor we want to add to this Vextor.
		* @return The resulting Vextor.
		**/
		Vextor operator + (const Vextor & v) const;

		/**
		* @brief Substracts a Vextor to this Vextor.
		* @param v The Vextor we want to subtract to this Vextor.
		* @return The resulting Vextor.
		**/
		Vextor operator - (const Vextor & v) const;

		/**
		* @brief Resizes a Vextor by a scalar.
		* @param s The scalar with which to resize the Vextor.
		* @return The resulting Vextor.
		**/
		Vextor operator * (float s) const;

		/**
		* @brief Resizes a Vextor by a scalar.
		* @param s The scalar with which to resize the Vextor.
		* @return The resulting Vextor.
		**/
		Vextor operator / (float s) const;

		/**
		* @brief Reverses the Vextor.
		* @return The reversed Vextor.
		**/
		Vextor operator - () const; 

		/**
		* @brief Adds a Vextor to this Vextor, and also saves changes in the first Vextor.
		* @param v The Vextor we want to add to this Vextor.
		**/
		void operator += (const Vextor & v);

		/**
		* @brief Subtracts a Vextor to this Vextor, and also saves changes in the first Vextor.
		* @param v The Vextor we want to subtract to this Vextor.
		**/
		void operator -= (const Vextor & v);

		/**
		* @brief Resizes the Vextor, and also saves changes in the first Vextor.
		* @param s The scalar by which we want to resize the Vextor.
		**/
		void operator *= (float s);

		/**
		* @brief Resizes the Vextor, and also saves changes in the first Vextor.
		* @param s The scalar by which we want to resize the Vextor.
		**/
		void operator /= (float s);

		/**
		* @brief Calculates the dot product of two Vextors.
		* @return The dot product of the two Vextors.
		**/
		float operator * (const Vextor & v) const;

		/**
		* @brief Applies a transformation Matrix to the Vextor.
		* @param m The Matrix to use for the transformation.
		* @return The resulting Vextor of the transformation.
		**/
		Vextor operator * (const Matrix & m) const;

		/**
		* @brief Applies a transpose transformation Matrix to the Vextor.
		* @param m The Matrix to use for the transformation.
		* @return The resulting Vextor of the transformation.
		**/
		Vextor operator ^ (const Matrix & m) const;

		/**
		* @brief Applies a transformation Matrix to the Vextor (and stores the change).
		* @param m The Matrix to use for the transformation.
		**/
		inline void operator *= (const Matrix & m);

		/**
		* @brief Calculates the cross product of two Vextors.
		* @return The cross product of the two Vextors.
		**/
		float operator ^ (const Vextor & v) const;

		bool operator == (const Vextor & v) const;

		bool operator < (const Vextor & v) const;
		/**
		* @brief Gets the x value of the Vextor.
		* @return The x value of the Vextor.
		**/
		float getX() const;
		
		/**
		* @brief Gets the x value of the Vextor.
		* @return The x value of the Vextor.
		**/
		float getY() const;

		/**
		* @brief Sets the x value of the Vextor.
		* @param The x value of the Vextor.
		**/
		void setX(float x);

		/**
		* @brief Sets the x value of the Vextor.
		* @param The x value of the Vextor.
		**/
		void setY(float y);




	};


	inline float Vextor::getLength() const
	{
		return sqrt(x*x + y*y);
	}

	inline Vextor Vextor::getNormal() const 
	{
		return Vextor(-y, x);
	}

	inline float Vextor::normalize()
	{
		
		float len = getLength();

		if(len > 0)
			(*this) /= len;

		return len;
	}

	/**
	* Inline methods must have body in header.
	**/

	inline Vextor::Vextor() : x(0.0f), y(0.0f)
	{
	}

	inline Vextor::Vextor(float x, float y) : x(x), y(y)
	{
	}

	inline Vextor Vextor::operator + (const Vextor & v) const
	{
		return Vextor(x + v.getX(), y + v.getY());
	}

	inline Vextor Vextor::operator - (const Vextor & v) const
	{
		return Vextor(x - v.getX(), y - v.getY());
	}
	
	inline Vextor Vextor::operator * (float s) const
	{
		return Vextor(x*s, y*s);
	}

	inline Vextor Vextor::operator / (float s) const
	{
		return Vextor(x/s, y/s);
	}

	inline Vextor Vextor::operator - () const
	{
		return Vextor(-x, -y);
	}

	inline void Vextor::operator += (const Vextor & v) 
	{
		x += v.getX();
		y += v.getY();
	}

	inline void Vextor::operator -= (const Vextor & v) 
	{
		x -= v.getX();
		y -= v.getY();
	}

	inline void Vextor::operator *= (float s)
	{
		x *= s;
		y *= s;
	}

	inline void Vextor::operator /= (float s)
	{
		x /= s;
		y /= s;
	}

	inline float Vextor::operator * (const Vextor & v) const
	{
		return x * v.getX() + y * v.getY();
	}

	inline Vextor Vextor::operator * (const Matrix & m) const
	{
		return Vextor((m.get0()*x + m.get2()*y), (m.get1()*x + m.get3()*y));
	}

	inline Vextor Vextor::operator ^ (const Matrix & m) const
	{
		return Vextor((m.get0()*x + m.get1()*y), (m.get2()*x + m.get3()*y));
	}

	inline void Vextor::operator *= (const Matrix & m)
	{
		x *= m.get0(); x += (m.get2()*y);
		y *= m.get3(); y += (m.get1()*x);
	}

	inline float Vextor::operator ^ (const Vextor & v) const
	{
		return x * v.getY() - y * v.getX();
	}


	inline bool Vextor::operator == (const Vextor & v) const
	{
		return getLength() == v.getLength();
	}

	inline bool Vextor::operator < (const Vextor & v) const
	{
		return getLength() < v.getLength();
	}
	/**
	* Accessor methods
	**/

	inline float Vextor::getX() const
	{
		return x;
	}

	inline float Vextor::getY() const
	{
		return y;
	}

	inline void Vextor::setX(float x)
	{
		this->x = x;
	}

	inline void Vextor::setY(float y)
	{
		this->y = y;
	}
	
	// Typedefs
	typedef boost::shared_ptr<Vextor> pVextor;

}//love

#endif
