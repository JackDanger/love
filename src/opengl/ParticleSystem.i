%{#include "ParticleSystem.h"%}

namespace love_opengl
{
	class ParticleSystem
	{
	private:
	public:
		void setBufferSize(unsigned int size);
		void setEmissionRate(int rate);
		void setLifetime(float life);
		void setParticleLife(float min, float max = 0);
		void setDirection(float direction, float spread = 0);
		void setSpeed(float min, float max = 0);
		void setGravity(float min, float max = 0);
		void setRadialAcceleration(float min, float max = 0);
		void setTangentialAcceleration(float min, float max = 0);
		void setColor(pColor color);
		void setColor(pColor start, pColor end);
		void setColor(pColor start, pColor end, float variation);
		void setColorVariation(float variation);
		
		unsigned int getBufferSize() const;
		int getEmissionRate() const;
		float getLifetime() const;
		
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