#include "Bezier.h"

using std::vector;

namespace love
{
	
	Bezier::Bezier() : num(0)
	{
	}
	
	Bezier::~Bezier()
	{
	}

	const vector<Vector> & Bezier::getPoints() const
	{
		return points;
	}

	void Bezier::first(float x1, float y1, 
		float x2, float y2, 
		float x3, float y3,
		float x4, float y4)
	{

		// Only do this once.
		if(!points.empty()) return;

		points.push_back(Vector(x1, y1));
		points.push_back(Vector(x2, y2));
		points.push_back(Vector(x3, y3));
		points.push_back(Vector(x4, y4));

		num++;

	}

	void Bezier::next(float x1, float y1, 
		float x2, float y2, 
		float x3, float y3)
	{
			
		// Only do this if first has been called.
		if(points.empty()) return;

		points.push_back(Vector(x1, y1));
		points.push_back(Vector(x2, y2));
		points.push_back(Vector(x3, y3));

		num++;
	}

	Vector Bezier::getPoint(float t)
	{
		// This is how much "t-time" each bezier gets.
		float rt = 1.0f/(float)num;

		// This must be the Bezier we're at.
		int bn = (int)(t/rt);

		if(bn >= num) bn = num - 1;

		// Convert into t for this bezier.
		float bt = ((t - (bn*rt))/rt);

		// Find starting vector
		int sv = (bn > 0) ? bn * 3 : 0;
		
		// The four points 
		const Vector & p0 = points[sv];
		const Vector & p1 = points[sv+1];
		const Vector & p2 = points[sv+2];
		const Vector & p3 = points[sv+3];

		float   ax, bx, cx;
		float   ay, by, cy;
		float   tSquared, tCubed;

		cx = 3.0f * (p1.getX() - p0.getX());
		bx = 3.0f * (p2.getX() - p1.getX()) - cx;
		ax = p3.getX() - p0.getX() - cx - bx;

		cy = 3.0f * (p1.getY() - p0.getY());
		by = 3.0f * (p2.getY() - p1.getY()) - cy;
		ay = p3.getY() - p0.getY() - cy - by;

		/* calculate the curve point at parameter value t */

		tSquared = bt * bt;
		tCubed = tSquared * bt;

		float x = (ax * tCubed) + (bx * tSquared) + (cx * bt) + p0.getX();
		float y = (ay * tCubed) + (by * tSquared) + (cy * bt) + p0.getY();

		return Vector(x, y);
	}

	void  Bezier::setPoint(int index, float x, float y)
	{
		if(index >= (int)points.size())
			return;

		points[index].setX(x);
		points[index].setX(y);
	}
	
} // love
