%{#include "ParticleSystem.h"%}

namespace love_opengl
{
	class ParticleSystem
	{
	private:
	public:
		void setBufferSize(unsigned int size);
		void setSprite(pImage sprite);
		
		void setEmissionRate(int rate);
		void setLifetime(float life);
		
		void setParticleLife(float min, float max = 0);
		void setPosition(float x, float y);
		void setDirection(float direction, float spread = 0);
		void setRelativeDirection(bool relative);
		
		void setSpeed(float min, float max = 0);
		void setGravity(float min, float max = 0);
		void setRadialAcceleration(float min, float max = 0);
		void setTangentialAcceleration(float min, float max = 0);
		
		void setSize(float size);
		void setSize(float start, float end);
		void setSize(float start, float end, float variation);
		void setSizeVariation(float variation);
		
		void setRotation(float rotation);
		void setRotation(float start, float end);
		void setRotation(float start, float end, float variation);
		void setRotationVariation(float variation);
		
		void setColor(pColor color);
		void setColor(pColor start, pColor end);
		
		float getDirection();
		
		int count() const;
		
		void start();
		void stop();
		void pause();
		void reset();
		
		bool isActive() const;
		bool isEmpty() const;
		bool isFull() const;
		
		void update(float dt);
	};
	
	typedef boost::shared_ptr<ParticleSystem> pParticleSystem;
}

%template(SmartParticleSystem) boost::shared_ptr<love_opengl::ParticleSystem>;