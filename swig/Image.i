%{#include "Image.h"%}

namespace love
{
	class Image : public Sprite
	{
	private:
	public:
	};
	
	typedef boost::shared_ptr<Image> pImage;
}

%template(SmartImage) boost::shared_ptr<love::Image>;
