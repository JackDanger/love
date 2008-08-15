%{#include "CircleShape.h"%}

namespace love_box2d
{
	class CircleShape : public Shape
	{
	public:
		float getRadius() const;
	};
	
	typedef boost::shared_ptr<CircleShape> pCircleShape;
}

%template(SmartCircleShape) boost::shared_ptr<love_box2d::CircleShape>;
