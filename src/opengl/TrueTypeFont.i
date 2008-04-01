%{#include "TrueTypeFont.h"%}

namespace love_opengl
{
	class TrueTypeFont : public Font
	{
	public:
	};
	
	typedef boost::shared_ptr<TrueTypeFont> pTrueTypeFont;
}

%template(SmartTrueTypeFont) boost::shared_ptr<love_opengl::TrueTypeFont>;
