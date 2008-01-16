%{#include "Sprite.h"%}

namespace love
{
	class Sprite
	{
	public:
		float getWidth() const;
		float getHeight() const;
		float getAlpha() const;
		void setAlpha(float alpha);
		virtual void update(float dt) = 0;
	};
	
	typedef boost::shared_ptr<Sprite> pSprite;
}

%template(SmartSprite) boost::shared_ptr<love::Sprite>;