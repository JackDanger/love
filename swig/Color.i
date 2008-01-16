%{#include "Color.h"%}

namespace love
{
	class Color
	{
	private:
	public:
		int getRed() const;
		int getGreen() const;
		int getBlue() const;
		int getAlpha() const;
		virtual void update(float dt);
	};
	
	typedef boost::shared_ptr<Color> pColor;
}

%extend love::Color 
{
	const char* __str__()
	{
        static char buffer[255];
        sprintf(buffer,"Color(%i,%i,%i,%i)",
				self->getRed(), self->getGreen(), self->getBlue(), self->getAlpha());
        return buffer;
	}
}

%template(SmartColor) boost::shared_ptr<love::Color>;