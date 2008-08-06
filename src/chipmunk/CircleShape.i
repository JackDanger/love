%{#include "CircleShape.h"%}

namespace love_chipmunk
{
	class CircleShape : public Shape
	{
	public:
	};
	
	typedef boost::shared_ptr<CircleShape> pCircleShape;
}

%template(SmartCircleShape) boost::shared_ptr<love_chipmunk::CircleShape>;
