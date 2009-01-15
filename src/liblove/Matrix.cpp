#include "Matrix.h"

// STD
#include <cstring>
#include <cmath>

// LOVE
#include "Vector.h"

namespace love
{
	Matrix::Matrix()
	{
		memset(e, 0, sizeof(float)*9);

		e[0][0] = 1; e[0][1] = 0; e[0][2] = 0;
		e[1][0] = 0; e[1][1] = 1; e[1][2] = 0;
		e[2][0] = 0; e[2][1] = 0; e[2][2] = 1;
	}

	Matrix::~Matrix()
	{
	}


	/**
	*			     [ 0,0 0,1 0,2 ]
	*			     [ 1,0 1,1 1,2 ]
	*			     [ 2,0 2,1 2,2 ]
	* [ 0,0 0,1 0,2 ]
	* [ 1,0 1,1 1,2 ]
	* [ 2,0 2,1 2,2 ]
	**/	

	Matrix Matrix::operator * (const Matrix & m) const
	{
		Matrix t;

		// First row:
		t.e[0][0] = (e[0][0] * m.e[0][0]) + (e[0][1] * m.e[1][0]) + (e[0][2] * m.e[2][0]);
		t.e[0][1] = (e[0][0] * m.e[0][1]) + (e[0][1] * m.e[1][1]) + (e[0][2] * m.e[2][1]);
		t.e[0][2] = (e[0][0] * m.e[0][2]) + (e[0][1] * m.e[1][2]) + (e[0][2] * m.e[2][2]);

		t.e[1][0] = (e[1][0] * m.e[1][0]) + (e[1][1] * m.e[1][0]) + (e[1][2] * m.e[2][0]);
		t.e[1][1] = (e[1][0] * m.e[1][1]) + (e[1][1] * m.e[1][1]) + (e[1][2] * m.e[2][1]);
		t.e[1][2] = (e[1][0] * m.e[1][2]) + (e[1][1] * m.e[1][2]) + (e[1][2] * m.e[2][2]);

		t.e[2][0] = (e[2][0] * m.e[0][0]) + (e[2][1] * m.e[1][0]) + (e[2][2] * m.e[2][0]);
		t.e[2][1] = (e[2][0] * m.e[0][1]) + (e[2][1] * m.e[1][1]) + (e[2][2] * m.e[2][1]);
		t.e[2][2] = (e[2][0] * m.e[0][2]) + (e[2][1] * m.e[1][2]) + (e[2][2] * m.e[2][2]);

		return t;
	}

	void Matrix::operator *= (const Matrix & m) const
	{
		Matrix t = (*this) * m;
		memcpy((void*)this->e, (void*)t.e, sizeof(float)*9);
	}

	void Matrix::setTranslation(float x, float y)
	{
		e[0][0] = 1; e[0][1] = 0; e[0][2] = x;
		e[1][0] = 0; e[1][1] = 1; e[1][2] = y;
		e[2][0] = 0; e[2][1] = 0; e[2][2] = 1;
	}

	void Matrix::setRotation(float rad)
	{
		float c = cos(rad), s = sin(rad);
		e[0][0] = c; e[0][1] = -s; e[0][2] = 0;
		e[1][0] = s; e[1][1] = c; e[1][2] = 0;
		e[2][0] = 0; e[2][1] = 0; e[2][2] = 1;
	}

	void Matrix::setScale(float sx, float sy)
	{
		e[0][0] = sx; e[0][1] = 0; e[0][2] = 0;
		e[1][0] = 0; e[1][1] = sy; e[1][2] = 0;
		e[2][0] = 0; e[2][1] = 0; e[2][2] = 1;
	}

	void Matrix::translate(float x, float y)
	{
		Matrix t;
		t.setTranslation(x, y);
		this->operator *=(t);
	}

	void Matrix::rotate(float rad)
	{
		Matrix t;
		t.setRotation(rad);
		this->operator *=(t);
	}

	void Matrix::scale(float sx, float sy)
	{
		Matrix t;
		t.setScale(sx, sy);
		this->operator *=(t);
	}

	void Matrix::transform(Vector * dst, Vector * src, int size)
	{
		for(int i = 0;i<size;i++)
			dst[i] = src[i] * (*this);
	}


	void Matrix::transform(vertex2v2t * dst, vertex2v2t * src, int size)
	{
		for(int i = 0;i<size;i++)
		{
			// Store in temp variables in case src = dst
			float x = e[0][0]*src[i].x+e[0][1]*src[i].y+e[0][2];
			float y = e[1][0]*src[i].x+e[1][1]*src[i].y+e[1][2];

			dst[i].x = x;
			dst[i].y = y;
		}
	}


} // love
