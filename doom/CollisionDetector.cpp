
#include "CollisionDetector.h"
#include "Grid.h"

#include "CollisionGame.h"
#include "Core.h"
#include "Event.h"

#include <float.h>


namespace love
{


	CollisionDetector::CollisionDetector()
	{
	}

	CollisionDetector::~CollisionDetector()
	{
	}


	bool CollisionDetector::find_mtd(vector<Vextor> & axis, vector<float> & t_axis, Vextor & N, float & t)
	{


		if(axis.size() != t_axis.size())
			return false;

		int size = (int)axis.size();

		// Look for collisions forward in time first
		int min_i = -1;
		t = 0.0f;

		for(int i=0;i<size;i++)
		{
			if(t_axis[i] > 0 && t_axis[i] > t)
			{
				min_i = i;
				t = t_axis[i];
				N = axis[i];
				N.normalize();
			}
		}

		// Found collision
		if(min_i != -1)
			return true;

		// Look for overlaps

		for(int i=0;i<size;i++)
		{
			float n = axis[i].getLength();

			if(n == 0) continue;

			axis[i] /= n; // Normalize
			t_axis[i] /= n;

			if(t_axis[i] > t || min_i == -1)
			{
				min_i = i;
				t = t_axis[i];
				N = axis[i];

			}
		}

		return (min_i != -1);
	}




	void CollisionDetector::calculateInterval(pBody & b, Vextor & axis, interval& intr)
	{



		/**
		* For each vector that spans between the origin and a vertex in the polygon, we take the
		* dot product of this vector and the axis. This will give us the projected distance of the vector
		* from the origin to the vertex along the axis. Keeping the min and max values found will give us
		* an interval with which we can compare other Polygons.
		**/

		const vector<Vextor> & points  = b.getVertices();

		intr.min = intr.max = axis * points[0];
		
		for(unsigned int i=1;i<points.size();i++)
		{
			float projected = axis * points[i];

			if(projected < intr.min)
				intr.min = projected;
			else if(projected > intr.max)
				intr.max = projected;
		}
	}

	float CollisionDetector::getOverlap(interval & i1, interval & i2)
	{

		    float d0 = i1.max - i2.min;
			float d1 = i2.max - i1.min;
			float depth = (d0 < d1)? d0 : d1; 

			return depth;
	}


	bool CollisionDetector::axisSeparates(	pBody & b1, pBody & b2, 
											Vextor & axis, 
											Vextor & xPosition, Vextor & xVelocity, Matrix & xOrientation, 
											float & t)
	{

		interval i1, i2;
		calculateInterval(b1, axis ^ xOrientation, i1);
		calculateInterval(b2, axis, i2);

		float h = xPosition * axis;
		i1.min += h;
		i1.max += h;

		float d0 = i1.min - i2.max; // if overlapped, do < 0
		float d1 = i2.min - i1.max; // if overlapped, d1 > 0

		// separated, test dynamic intervals
		if (d0 > 0.0f || d1 > 0.0f) 
		{
			float v = xVelocity * axis;

			// small velocity, so only the overlap test will be relevant. 
			if (fabs(v) < 0.0000001f)
			{
				t = 0.0f;
				return true;
			}

			float t0 =-d0 / v; // time of impact to d0 reaches 0
			float t1 = d1 / v; // time of impact to d0 reaches 1

			if (t0 > t1) { float temp = t0; t0 = t1; t1 = temp; }
			t  = (t0 > 0.0f)? t0 : t1;

			if (t < 0.0f || t > 1.0f)
				return true;

			return false;
		}
		else
		{
			// overlap. get the interval, as a the smallest of |d0| and |d1|
			// return negative number to mark it as an overlap
			t = (d0 > d1)? d0 : d1;
			return false;
		}

	}

	bool CollisionDetector::intersects(pBody & b1, pBody & b2, Vextor & N, float & t)
	{

		// Relative orientation
		Matrix xOrientation	= b1.getOrientation() ^ b2.getOrientation();

		// Relative position
		Vextor xPosition	= (b1.getPosition() - b2.getPosition()) ^ b2.getOrientation() ;

		// Relative velocity
		Vextor xVelocity	= (b1.getDisplacement() - b2.getDisplacement()) ^ b2.getOrientation();

		// Holds all the axis tested
		vector<Vextor> axis;
		axis.reserve(32);

		// Holds the time of collision for each axis, 
		// or an overlap depth if overlapping.
		vector<float> t_axis;
		t_axis.reserve(32);




		float v = xVelocity * xVelocity; // speed squared


		// Check normal to velocity vector
		if(fabs(v) > 0.0000001f)
		{

			// Linear vel. is orientation independent, and thus
			// must not be transformed.
			axis.push_back(xVelocity.getNormal());
			t_axis.push_back(0.0f);
			if(axisSeparates(b1, b2, axis.back(),xPosition, xVelocity, xOrientation ,t_axis.back()))
				return false;
		}


		// Get points from first polygon
		const vector<Vextor> & points  = b1.getVertices();
		int num_points  = (int)b1.getVertices().size();

		// Do not do this for points
		if(num_points > 1)
		{

			// Check all edges of the first polygon
			for(int j = num_points - 1, i = 0; i < num_points; j = i, i++)
			{
				// Builds the edge
				Vextor edge =  points[i] - points[j];
				axis.push_back(edge.getNormal() * xOrientation);
				t_axis.push_back(0.0f);
				if(axisSeparates(b1, b2, axis.back(),xPosition, xVelocity, xOrientation ,t_axis.back()))
					return false;
			}
		}

		// Get points from second polygon
		const vector<Vextor> & points2  = b2.getVertices();
		int num_points2  = (int)b2.getVertices().size();

		// Do not do this for points
		if(num_points2 > 1)
		{

			// Check all edges of the second polygon
			for(int j = num_points2 - 1, i = 0; i < num_points2; j = i, i++)
			{
				// Builds the edge
				Vextor edge =  points2[i] - points2[j];
				axis.push_back(edge.getNormal());
				t_axis.push_back(0.0f);
				if(axisSeparates(b1, b2, axis.back(),xPosition, xVelocity, xOrientation ,t_axis.back()))
					return false;
			}

		}

		// Special case for line segments
		if(num_points2 == 2)
		{
			Vextor edge(points2[1].getX() - points2[0].getX(), points2[1].getY() - points2[0].getY());
			axis.push_back(edge.getNormal());
			t_axis.push_back(0.0f);
			if(axisSeparates(b1, b2, axis.back(),xPosition, xVelocity, xOrientation ,t_axis.back()))
				return false;
		}

		// Special case for line segments
		if(num_points == 2)
		{
			Vextor edge(points[1].getX() - points[0].getX(), points[1].getY() - points[0].getY());
			axis.push_back(edge.getNormal() * xOrientation);
			t_axis.push_back(0.0f);
			if(axisSeparates(b1, b2, axis.back(),xPosition, xVelocity, xOrientation ,t_axis.back()))
				return false;
		}


		find_mtd(axis, t_axis, N, t);

		if(N * xPosition < 0.0f)
			N *= -1.0f;

		N = N * b2.getOrientation();

		return true;
	}

	

	bool CollisionDetector::intersects(pBody &b1, pBody &b2)
	{
		// Don't check for collision  if both objects are unmovable.
		if(!b1.isMovable() && !b2.isMovable())
			return false;

		// Two points cannot intersect
		if(b1.getVertices().size() == 1 && b2.getVertices().size() == 1)
			return false;


		Vextor N;			// The normalized separation axis
		float t = 0.0f;		// Time of collision

		// Do test
		bool collided = intersects(b1, b2, N, t);

		if(collided)
		{
			if(t > 0.0f && t < 1.0f)
				handleCollision(b1, b2, N, t);
			else
				handleOverlap(b1, b2, N * -t);
		}

		return collided;

	}

	void CollisionDetector::handleCollision(pBody& b1, pBody& b2, Vextor& N, float t)
	{
		Vextor D = b1.getDisplacement() - b2.getDisplacement();

		float n  = D * N;
		
		Vextor Dn = N * n;
		Vextor Dt = D - Dn;
		
		if (n > 0.0f) Dn = Vextor(0, 0);

		float dt  = Dt * Dt;
		float CoF = b1.getFriction();
		
		if (dt < b1.getGlue() * b1.getGlue()) 
			CoF = 1.01f;

		D = (Dn * (-1.0f + b1.getRestitution())) - Dt * CoF;

		float m0 = b1.getInverseMass();
		float m1 = b2.getInverseMass();
		float m  = m0 + m1;
		float r0 = m0 / m;
		float r1 = m1 / m;
		
		b1.setDisplacement(b1.getDisplacement() + D * r0);
		b2.setDisplacement(b2.getDisplacement() - D * r1);
	}

	void CollisionDetector::handleOverlap(pBody& b1, pBody& b2, Vextor& mtd)
	{
		if(!b2.isMovable())
		{
			b1.setPosition( b1.getPosition() + mtd);
		}else if(!b1.isMovable())
		{
			b2.setPosition( b2.getPosition() - mtd);
		}else
		{
			b1.setPosition( b1.getPosition() + mtd * 0.5f);
			b2.setPosition( b2.getPosition() - mtd * 0.5f);
		}

		Vextor N = mtd;
		N.normalize();
		handleCollision(b1, b2, N, 0.0f);
	}

	void CollisionDetector::resolveGrid(const Container<Body> & bodies, pBody & b, Cell * c)
	{	
		// Return if Cell does not exist
		if(c == 0)
			return;

		// Continue if the Grid this Cell is on is empty.
		if(c->getParentGrid()->isEmpty())
		{
			resolveGrid(bodies, b, c->getParentCell());
		}

		// Check this Cell
		resolveCell(bodies, b, c);

		// Check neighboring cells
		resolveCell(bodies, b, c->getNW());
		resolveCell(bodies, b, c->getW());
		resolveCell(bodies, b, c->getSW());
		resolveCell(bodies, b, c->getS());
		resolveCell(bodies, b, c->getSE());
		resolveCell(bodies, b, c->getE());
		resolveCell(bodies, b, c->getNE());
		resolveCell(bodies, b, c->getN());

		// Do same thing for parent
		resolveGrid(bodies, b, c->getParentCell());

	}

	void CollisionDetector::resolveCell(const Container<Body> & bodies, pBody & b, Cell * c)
	{	

		numcells++;

		// Return if Cell does not exist
		if(c == 0)
			return;

		// Return if the cell is empty
		if(c->isEmpty())
			return;

		const std::map<int,Body *> & bmap = bodies.getMap();
		
		// Check all elements in this Cell
		for each(int i in c->getElements())
		{
			if(i != b->getId())
			{
				Body * b2 = bmap.find(i)->second;
				bool collided = intersects(*b, *b2);

				if(collided)
				{
					//Event e;
					//e.setType(Event::LOVE_COLLIDE);
					//e.addData(b->getId());
					//e.addData(b2->getId());
					//Core::eventFired(e);
				}

			}
		
		}

	}

	void CollisionDetector::resolve(const Container<Body> & bodies)
	{
		
		for(bodies.begin();!bodies.end();bodies.next())
			resolveGrid(bodies, bodies.value(), bodies.value()->getParentCell());
	}

	void CollisionDetector::resolve(pBody &b1, pBody &b2)
	{
		bool collided = intersects(b1, b2);

		if(collided)
		{
			/**
			Event e;
			e.setType(Event::LOVE_COLLIDE);
			e.addData(b1.getId());
			e.addData(b2.getId());
			Core::eventFired(e);
			**/
		}
	}


}//love