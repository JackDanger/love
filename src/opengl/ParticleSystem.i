%{#include "ParticleSystem.h"%}

namespace love_opengl
{
	class ParticleSystem
	{
	private:
	public:
		void setBufferSize(unsigned int size);
		unsigned int getBufferSize() const;
		int count() const;
		bool isEmpty() const;
		bool isFull() const;
		void update(float dt);
	};
	
	typedef boost::shared_ptr<ParticleSystem> pParticleSystem;
}

%template(SmartParticleSystem) boost::shared_ptr<love_opengl::ParticleSystem>;