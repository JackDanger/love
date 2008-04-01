%{#include "Color.h"%}

namespace love_opengl
{
	class Color
	{
	private:
	public:
		void setRed(int red);
		void setGreen(int green);
		void setBlue(int blue);
		void setAlpha(int alpha);
		int getRed() const;
		int getGreen() const;
		int getBlue() const;
		int getAlpha() const;
		virtual void update(float dt);
	};
	
	typedef boost::shared_ptr<Color> pColor;
}

%template(SmartColor) boost::shared_ptr<love_opengl::Color>;