/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
* 
* @author Anders Ruud
* @date 2009-01-09
*/

#ifndef LOVE_MATRIX_H
#define LOVE_MATRIX_H

// STD
#include <cmath>

namespace love
{
	/**
	* 2D Vector class.
	* 
	* @author Anders Ruud
	* @date 2006-05-13
	**/
	class Matrix
	{
		friend class Vector;

	public:

		// The elements of the matrix.
		// The first dimension is rows.
		//       j1  j2  j3
		// i0: [ 0,0 0,1 0,2 ]
		// i1: [ 1,0 1,1 1,2 ]
		// i2: [ 2,0 2,1 2,2 ]
		float e[3][3];

		/**
		* Creates a new identity matrix.
		**/
		Matrix();
		~Matrix();

		Matrix operator * (const Matrix & m) const;
		void operator *= (const Matrix & m) const;

		void setTranslation(float x, float y);
		void setRotation(float rad);
		void setScale(float sx, float sy);

		void translate(float x, float y);
		void rotate(float rad);
		void scale(float sx, float sy);

	};

} //love

#endif// LOVE_MATRIX_H
