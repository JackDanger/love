%{#include "Image.h"%}

namespace love_opengl
{
	class Image : public Sprite
	{
	public:
	};
	
	typedef boost::shared_ptr<Image> pImage;
}

%template(SmartImage) boost::shared_ptr<love_opengl::Image>;
