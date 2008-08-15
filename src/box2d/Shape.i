%{#include "Shape.h"%}

namespace love_box2d
{
	class Shape
	{
	public:
	
		int getType() const;
		
		void setFriction(float friction);
		void setRestitution(float restitution);
		void setDensity(float density);
		void setSensor(bool sensor);

		float getFriction() const;
		float getRestituion() const;
		float getDensity() const;
		bool isSensor() const;
		
		boost::shared_ptr<Body> getBody() const;
		bool testPoint(float x, float y) const;

		void setCategoryBits(int bits);
		int getCategoryBits() const;

		void setMaskBits(int bits);
		int getMaskBits() const;
	};
	
	typedef boost::shared_ptr<Shape> pShape;
}

%template(SmartShape) boost::shared_ptr<love_box2d::Shape>;
