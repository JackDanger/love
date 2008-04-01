%{#include "Space.h"%}

namespace love_chipmunk
{
	class Space
	{
	public:
		void update(float dt);

		void setGravity(float x, float y);
		void setGravity(float y);
		void setDamping(float d);

		void resizeStaticHash(float dim, int count);
		void resizeActiveHash(float dim, int count);
	};
	
	typedef boost::shared_ptr<Space> pSpace;
}

%template(SmartSpace) boost::shared_ptr<love_chipmunk::Space>;
