%{#include "SegmentShape.h"%}

namespace love_chipmunk
{
	class SegmentShape : public Shape
	{
	public:
		pVector getFirst();
		pVector getSecond();
	};
	
	typedef boost::shared_ptr<SegmentShape> pSegmentShape;
}

%template(SmartSegmentShape) boost::shared_ptr<love_chipmunk::SegmentShape>;
