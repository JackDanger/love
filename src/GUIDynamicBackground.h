/**
* @file GUIDynamicBackground.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUIDynamicBackground.
**/

#ifndef LOVE_GUIDYNAMICBACKGROUND_H
#define LOVE_GUIDYNAMICBACKGROUND_H

// LOVE
#include "AbstractEntity.h"
#include "Color.h"
#include "Vector.h"
#include "SmoothAnimatedColor.h"

// STL
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class GUIDynamicBackground
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GUIDynamicBackground : AbstractEntity
	{
	private:

		float width;
		float height;

		int precision;

		float triangleWidth;
		float triangleHeight;

		std::vector<pAbstractColor> colors;

		
		Vector vel;

		bool line;

	public:

		Vector center;

		/**
		* @brief Contructs an empty GUIDynamicBackground.
		**/
		GUIDynamicBackground();
		GUIDynamicBackground(float width, float height);

		virtual ~GUIDynamicBackground();

		void setSize(float width, float height);

		void render();
		void update(float dt);

		Vector getPosition(int i, int j);
		Color getColor(float x, float y);

		void setLine(bool line);

	};

	typedef boost::shared_ptr<GUIDynamicBackground> pGUIDynamicBackground;

} // love

#endif

