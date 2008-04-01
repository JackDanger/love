%{#include "Font.h"%}

namespace love_opengl
{
	class Font
	{
	public:
		virtual float getHeight() const;
		virtual float getWidth(const char * line) const;
		void setLineHeight(float height);
		virtual float getLineHeight() const;
	};
	
	typedef boost::shared_ptr<Font> pFont;
}

%template(SmartFont) boost::shared_ptr<love_opengl::Font>;
