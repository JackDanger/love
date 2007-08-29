/**
* @file Bezier.h
* @author Anders Ruud
* @date 2007-08-28
* @brief Contains definition for class Bezier.
**/

#ifndef LOVE_BEZIER_H 
#define LOVE_BEZIER_H 

// LOVE
#include "Vector.h"
#include "Object.h"

// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

using std::vector;

namespace love
{

	/**
	* @class Bezier
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-28
	* @brief Represents a series of cubic Bezier curves.
	**/
	class Bezier : public Object
	{
	private:
	
		// Contains all the points.
		// The first four points form a curve, then the 
		// last of the four first, and the three next form a 
		// curve, and so on.
		vector<Vector> points;

		// Number of Beziers.
		int num;

	public:
	
		/**
		* @brief Constructs an empty Bezier.
		**/
		Bezier();
		
		/**
		* @brief Destructor.
		**/
		~Bezier();

		const vector<Vector> & getPoints() const;

		void first(float x1, float y1, 
			float x2, float y2, 
			float x3, float y3,
			float x4, float y4);

		void next(float x1, float y1, 
			float x2, float y2, 
			float x3, float y3);

		Vector getPoint(float t);
		
		void setPoint(int index, float x, float y);

		
	}; // Bezier
	
	typedef boost::shared_ptr<Bezier> pBezier;
	
} // love

#endif
