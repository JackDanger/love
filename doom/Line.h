#ifndef LINE_H
#define LINE_H

#include "Shape.h"

namespace love 
{

	/**
	* @class Line
	* @version 1.0
	* @since 1.0
	* @author Kjell Ivar Storstein
	* @date 2006-01-15
	* @brief
	**/
	class Line : Shape
	{
	private:
		float x2, y2;
	public:
		Line(float x, float y, float x2, float y2);
		~Line();
		
		virtual void render();
	};

	typedef boost::shared_ptr<Line> pLine;
	
}// love

#endif