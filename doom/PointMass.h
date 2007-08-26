#ifndef LOVE_POINT_MASS_H
#define LOVE_POINT_MASS_H

#include "Object.h"
#include "Vextor.h"
#include "Matrix.h"

#include <vector>

using std::vector;

namespace love
{
	class PointMass : public Object
	{
	private:

		// Stores the points. 
		vector<Vextor> vertices;

		// The orientation is represented by a matrix transformation.
		Matrix orientation;

		// The angluar velocity.
		float angularVelocity;

		// The current angle.
		float angle;

		// The radius of the minimum bounding circle
		float radius;

	public:

		PointMass();
		~PointMass();

		void computeRadius();

		float getRadius();

		const Matrix & getOrientation() const;

		const vector<Vextor> & getVertices() const;
		void setVertices(vector<Vextor> vertices);

		void setOrientation(Matrix m);
		
		float getAngle() const;
		void setAngle(float angle);

		float getAngularVelocity() const;
		void setAngularVelocity(float angularVelocity);
	};

	typedef boost::shared_ptr<PointMass> pPointMass;
}

#endif