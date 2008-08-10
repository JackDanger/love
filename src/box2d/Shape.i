%{#include "Shape.h"%}

namespace love_box2d
{
	class Shape
	{
	public:
	};
	
	typedef boost::shared_ptr<Shape> pShape;
}

%template(SmartShape) boost::shared_ptr<love_box2d::Shape>;
