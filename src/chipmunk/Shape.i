%{#include "Shape.h"%}

namespace love_chipmunk
{
	class Shape
	{
	public:
		void setType(unsigned long type);
		unsigned long getType() const;
		void setGroup(unsigned long group);
		unsigned long getGroup() const;
		void setLayers(unsigned long layers);
		unsigned long getLayers() const;
		void setElasticity(float e);
		float getElasticity() const;
		void setFriction(float u);
		float getFriction() const;
		void setSurfaceVelocity(float x, float y);		
	};
	
	typedef boost::shared_ptr<Shape> pShape;
}

%template(SmartShape) boost::shared_ptr<love_chipmunk::Shape>;
