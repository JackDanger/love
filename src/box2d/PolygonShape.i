%{#include "PolygonShape.h"%}

namespace love_box2d
{
	class PolygonShape : public Shape
	{
	public:
	};
	
	typedef boost::shared_ptr<PolygonShape> pPolygonShape;
}

%template(SmartPolygonShape) boost::shared_ptr<love_box2d::PolygonShape>;
