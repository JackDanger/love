%{#include "Particlesystem.h"%}

namespace love
{
	class Particlesystem
	{
	protected:
	public:
		void setAutostart(bool autoStart);
		int getNumParticles() const;
		bool isAdditive() const;
		void reset();
		void setPosition(float x, float y);
		float getLifetime() const;
		void setLifetime(float lifetime);

		float getAge() const;
		void setLinger(float linger);
		float getLinger();
		bool isDead() const;
		bool isActive() const;
		void setParticlesPerSecond(float particlesPerSecond);
		void addColor(int r, int g, int b, int a = 255, float time = 1.0f);
		void setSprite(pSprite sprite);
		void setAdditiveBlending(bool additive);

		void setDirection(float min, float max, float var = 0.0f);
		void setDirection(float m);

		void setStartSpeed(float min, float max, float var = 0.0f);
		void setStartSpeed(float m);

		void setGravity(float min, float max, float var = 0.0f);
		void setGravity(float m);

		void setRadialAcc(float min, float max, float var = 0.0f);
		void setRadialAcc(float m);

		void setTangentialAcc(float min, float max, float var = 0.0f);
		void setTangentialAcc(float m);

		void setParticleLifetime(float min, float max, float var = 0.0f);
		void setParticleLifetime(float m);

		void setParticleSize(float min, float max, float var = 0.0f);
		void setParticleSize(float m);

		void setParticleSpin(float min, float max, float var = 0.0f);
		void setParticleSpin(float m);

		virtual void update(float dt);

	};

	typedef boost::shared_ptr<Particlesystem> pParticlesystem;

} // love

// Extensions
%extend love::Particlesystem 
{
	void setSprite(pImage sprite)
	{
		self->setSprite(sprite);
	}

}

%template(SmartParticlesystem) boost::shared_ptr<love::Particlesystem>;

