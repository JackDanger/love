#include "Polygon.h"

namespace love
{

	Polygon::Polygon()
	{
		setType(LOVE_TYPE_POLYGON);
	}

	Polygon::~Polygon()
	{
	}

	const vector<Vextor> & Polygon::getVertices() const
	{
		return vertices;
	}

	void Polygon::addPoint(float x, float y)
	{
		vertices.push_back(Vextor(x, y));
	}

	void Polygon::render()
	{
		glBegin(GL_POLYGON);
		for(int i = 0; i< vertices.size(); i++)
				glVertex2f(vertices[i].getX(), vertices[i].getY());

		glEnd();
	}


}// love
