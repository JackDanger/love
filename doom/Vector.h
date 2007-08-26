#ifndef VECTOR_H
#define VECTOR_H

#include "Shape.h"


namespace love 
{

	class Point;

	/**
	* @class Vector
	* @version 1.0
	* @since 1.0
	* @author Kjell Ivar Storstein
	* @date 2006-01-15
	* @brief 
	**/
	class Vector : public Shape
	{
	private:
		float xLength, yLength;

	public:	
		Vector();
		Vector(float xlen, float ylen);
		Vector(float x, float y, float xlen, float ylen);
		~Vector();
		
		void add(Vector & v);
		void sub(Vector & v);
		void mul(Vector & v);
		void mul(float f);
		void div(Vector & v);
		void div(float f);

		float dot(Vector & v);
		float dot(Point & p);
		float dot(float x, float y);
		void normalize();		

		float getLength();		
		float getAngle();
		float getXLength();
		float getYLength();
		void setXLength(float f);
		void setYLength(float f);

		Vector getNormal();

		virtual void render();
		void updatePos(float x, float y);


		// Operator overloads
		bool operator == (Vector &v);
		bool operator < (Vector &v);

		float operator * (Vector& v);	// Dot product
		void operator *= (Vector& v);	// Dot product (vector becomes)

		Vector operator * (float f);	
		void operator *= (float f);

		void operator /= (float f);

		Vector operator + (Vector& v);
		Vector operator - (Vector& v);

		void operator += (Vector& v);
		void operator -= (Vector& v);



	};
	
}//love

#endif
