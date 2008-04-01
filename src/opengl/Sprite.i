%{#include "Sprite.h"%}

namespace love_opengl
{
	class Sprite
	{
	public:
		float getWidth() const;
		float getHeight() const;
		virtual void update(float dt);
		void setCenter(float x, float y);
	};
	
	typedef boost::shared_ptr<Sprite> pSprite;
}

%template(SmartSprite) boost::shared_ptr<love_opengl::Sprite>;
