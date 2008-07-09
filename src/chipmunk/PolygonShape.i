%{#include "PolygonShape.h"%}

namespace love_chipmunk
{
	class PolygonShape : public Shape
	{
	public:
	};
	
	typedef boost::shared_ptr<PolygonShape> pPolygonShape;
}

%template(SmartPolygonShape) boost::shared_ptr<love_chipmunk::PolygonShape>;
