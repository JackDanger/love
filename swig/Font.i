%{#include "Font.h"%}

namespace love
{
	class Font
	{
	private:
	public:		
		virtual float getHeight();
		virtual float getWidth(const char * line);
		virtual void setLineHeight(float height);
		virtual float getLineHeight();
	};
	
	typedef boost::shared_ptr<Font> pFont;
}

%template(SmartFont) boost::shared_ptr<love::Font>;