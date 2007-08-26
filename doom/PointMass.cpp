#include "PointMass.h"

namespace love
{
	PointMass::PointMass()
	{
		angle = 0.0f;
		angularVelocity = 0.0f;
		orientation = Matrix(0.0f);
		setType(LOVE_TYPE_POINT_MASS);
	}

	PointMass::~PointMass()
	{
	}

	void PointMass::computeRadius()
	{
		float max_rad_squared = 0.0f;

		for(int i=0;i<(int)vertices.size();i++)
		{
			float x = vertices[i].getX();
			float y = vertices[i].getY();

			float pmax = x * x + y * y;

			if(pmax > max_rad_squared)
				max_rad_squared = pmax;
		}

		this->radius = sqrt(max_rad_squared);
	}
	
	float PointMass::getRadius(){ return radius; }

	const Matrix & PointMass::getOrientation() const { return orientation; }

	const vector<Vextor> & PointMass::getVertices() const { return vertices; }
	void PointMass::setVertices(vector<Vextor> vertices){ this->vertices = vertices; }

	void PointMass::setOrientation(Matrix m){ this->orientation = orientation; }
	
	float PointMass::getAngle() const { return angle; }
	void PointMass::setAngle(float angle){ this->angle = angle; }

	float PointMass::getAngularVelocity() const { return angularVelocity; }
	void PointMass::setAngularVelocity(float angularVelocity){ this->angularVelocity = angularVelocity; }

}//love