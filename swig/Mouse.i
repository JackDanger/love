%{#include "Mouse.h"%}

namespace love
{

	class Mouse : public Device
	{
	protected:	
	public:				
		virtual float getX() const = 0;
		virtual float getY() const = 0;
		virtual bool isDown(int button) const = 0;
		virtual void setVisible(bool visible) = 0;
		virtual bool isVisible() const = 0;
		virtual void setX(float x) = 0;
		virtual void setY(float y) = 0;
		virtual void setPosition(float x, float y) = 0;
	};
	
}