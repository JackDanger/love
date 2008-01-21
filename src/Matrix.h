/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MATRIX_H
#define LOVE_MATRIX_H

// STD
#include <cmath>

namespace love 
{

	/**
	* Basic 2x2 Matrix class.
	* | e0 e2 |
	* | e1 e3 |
	* 
	* @author Anders Ruud
	* @date 2006-04-26
	**/
	class Matrix
	{
	private:

		// The elements of a 2x2 Matrix
		// | e0 e2 |
		// | e1 e3 |
		float e0, e1, e2, e3;


	public:	

		/**
		* @brief Creates a new identity Matrix.
		**/
		Matrix();

		/**
		* @brief Creates a new Matrix.
		* @param e0 Element of the Matrix.
		* @param e1 Element of the Matrix.
		* @param e2 Element of the Matrix.
		* @param e3 Element of the Matrix.
		**/
		Matrix(float e0, float e1, float e2, float e3);

		/**
		* @brief Creates a new rotation Matrix.
		* @param rad The angle from which to create the Matrix.
		**/
		Matrix(float rad);

		/**
		* @brief Checks whether two Matrices are equal.
		* @param m The Matrix to compare with this Matrix.
		* @return True if they are equal, false otherwise.
		**/
		bool operator == (const Matrix & m) const;

		/**
		* @brief Adds two Matrices together.
		* @param m The Matrix to add with this one.
		* @return The resulting Matrix.
		**/
		Matrix operator + (const Matrix & m) const;

		/**
		* @brief Subtracts one Matrix from another.
		* @param m The Matrix to subtract with this one.
		* @return The resulting Matrix.
		**/
		Matrix operator - (const Matrix & m) const;

		/**
		* @brief Increases this Matrix by the specified Matrix.
		* @param m The Matrix to increase this one by.
		**/
		void operator += (const Matrix & m);

		/**
		* @brief Decreases this Matrix by the specified Matrix.
		* @param m The Matrix to decreases this one by.
		**/
		void operator -= (const Matrix & m);

		/**
		* @brief Performs a Matrix multiplication.
		* @param m The Matrix with which to multiply with.
		* @return The result Matrix of the multiplication.
		**/
		Matrix operator * (const Matrix & m) const;

		/**
		* @brief Multiplies the Matrix by a given scalar.
		* @param f The number by which to multiply the Matrix.
		* @return The resulting Matrix.
		**/
		Matrix operator * (float f) const;

		/**
		* @brief Multiplies the Matrix by a given scalar, and stores the result in this Matrix.
		* @param f The number by which to multiply the Matrix.
		**/
		void operator *= (float f);

		/**
		* @brief Divides the Matrix by a given scalar.
		* @param f The number by which to divide the Matrix.
		* @return The resulting Matrix.
		**/
		Matrix operator / (float f) const;

		/**
		* @brief Divides the Matrix by a given scalar, and stores the result in this Matrix.
		* @param f The number by which to divide the Matrix.
		* @return The resulting Matrix.
		**/
		void operator /= (float f);

		/**
		* @brief Calculates the Matrix product between this Matrix and the transpose of the parameter.
		* @return The resulting Matrix.
		**/
		Matrix operator ^ (const Matrix & m) const;

		/**
		* Provides read access to elements.
		***/
		float get0() const;
		float get1() const;
		float get2() const;
		float get3() const;

	}; // Matrix

	/**
	* Inline methods must be in header.
	**/

	inline Matrix::Matrix() : e0(1.0f), e1(0.0f), e2(0.0f), e3(1.0f)
	{
	}

	inline Matrix::Matrix(float e0, float e1, float e2, float e3) : e0(e0), e1(e1), e2(e2), e3(e3)
	{
	}

	inline Matrix::Matrix(float rad)
	{
		e0 = cos(rad);		e2 = sin(rad);
		e1 = -e2;			e3 = e0;
	}

	inline bool Matrix::operator == (const Matrix & m) const 
	{
		return (e0 == m.get0() && e1 == m.get1() && e2 == m.get2() && e3 == m.get3());
	}

	inline Matrix Matrix::operator + (const Matrix & m) const
	{
		return Matrix(e0 + m.get0(), e1 + m.get1(), e2 + m.get2(), e3 + m.get3());
	}

	inline Matrix Matrix::operator - (const Matrix & m) const
	{
		return Matrix(e0 - m.get0(), e1 - m.get1(), e2 - m.get2(), e3 - m.get3());
	}

	inline void Matrix::operator += (const Matrix & m)
	{
		e0 += m.get0();
		e1 += m.get1();
		e2 += m.get2();
		e3 += m.get3();
	}

	inline void Matrix::operator -= (const Matrix & m)
	{
		e0 -= m.get0();
		e1 -= m.get1();
		e2 -= m.get2();
		e3 -= m.get3();
	}

	inline Matrix Matrix::operator * (const Matrix & m) const
	{

		return Matrix(	(e0 * m.get0() + e2 * m.get1()),
						(e1 * m.get0() + e3 * m.get1()),
						(e0 * m.get2() + e2 * m.get3()),
						(e1 * m.get2() + e3 * m.get3()));
	}


	inline Matrix Matrix::operator * (float f) const
	{
		return Matrix(e0*f, e1*f, e2*f, e3*f);
	}

	inline void Matrix::operator *= (float f)
	{
		e0 *= f;
		e1 *= f;
		e2 *= f;
		e3 *= f;
	}

	inline Matrix Matrix::operator / (float f) const
	{
		return Matrix(e0/f, e1/f, e2/f, e3/f);
	}

	inline void Matrix::operator /= (float f)
	{
		e0 /= f;
		e1 /= f;
		e2 /= f;
		e3 /= f;
	}

	inline Matrix Matrix::operator ^ (const Matrix & m) const
	{

		return Matrix(	(e0 * m.get0() + e2 * m.get2()),
						(e1 * m.get0() + e3 * m.get2()),
						(e0 * m.get1() + e2 * m.get3()),
						(e1 * m.get1() + e3 * m.get3()));
	}

	/**
	* Accessor methods
	**/

	inline float Matrix::get0() const
	{
		return e0;
	}

	inline float Matrix::get1() const
	{
		return e1;
	}

	inline float Matrix::get2() const
	{
		return e2;
	}

	inline float Matrix::get3() const
	{
		return e3;
	}

}// namespace love

#endif // LOVE_MATRIX_H
