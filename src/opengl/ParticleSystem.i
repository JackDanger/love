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
		void setDirection(float direction);
		void setSpread(float spread);
		
		void setSpeed(float speed);
		void setSpeed(float min, float max);
		
		void setGravity(float gravity);
		void setGravity(float min, float max);
		
		void setRadialAcceleration(float acceleration);
		void setRadialAcceleration(float min, float max);
		
		void setTangentialAcceleration(float acceleration);
		void setTangentialAcceleration(float min, float max);
		
		void setSize(float size);
		void setSize(float start, float end);
		void setSize(float start, float end, float variation);
		void setSizeVariation(float variation);
		
		void setRotation(float rotation);
		void setRotation(float min, float max);
		
		void setSpin(float spin);
		void setSpin(float start, float end);
		void setSpin(float start, float end, float variation);
		void setSpinVariation(float variation);
		
		void setColor(pColor color);
		void setColor(pColor start, pColor end);
		
		float getX() const;
		float getY() const;
		float getDirection() const;
		float getSpread() const;
		
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