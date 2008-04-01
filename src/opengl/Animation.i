%{#include "Animation.h"%}

namespace love_opengl
{
	class Animation : public Sprite
	{
	private:
	public:
		void addFrame(float x, float y, float w, float h, float delay);
		void setMode(int mode);
		void play();
		void stop();
		void reset();
		void seek(int frame);
		int getCurrentFrame() const;
		void setDelay(int frame, float delay);
		void setSpeed(float speed);
		float getSpeed() const;
	};
	
	typedef boost::shared_ptr<Animation> pAnimation;
}

%template(SmartAnimation) boost::shared_ptr<love_opengl::Animation>;