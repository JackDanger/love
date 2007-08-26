#ifndef LOVE_PARTICLECONTROLLER_H
#define LOVE_PARTICLECONTROLLER_H

#include "Entity.h"
#include "Particle.h"
#include "GradientColor.h"
#include "Tileset.h"
#include <vector>

using std::vector;

namespace love
{
	/**
	 * @class ParticleController
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-08-23
	 * @brief This class handles the particles. It is made to be customized to INSANE degrees, but all Particle
	 *        actions should go through this.
	 **/
	class ParticleController : public Entity
	{
	private:
		vector<Particle> particles;
		GradientColor gradient;

		bool fade; //if the particle fades over time
		float lifetime; //how long the particles live (in seconds)
		float direction; //direction of particle emitter (in degrees of a circle)
		float directionMargin; //the margin for the direction of the particles
		float velocity; //initial velocity of the particles (in pixels/second)
		float acceleration; //how much the velocity changes (in pixels/second)
		float rotation; //how much the particles rotate (per second)
		float rotationMargin; //how much the rotation can deviate from the main (motherfucker)

		int width, height;
	public:
		Tileset * tiles;

		ParticleController();
		ParticleController(float x, float y, Color color);
		ParticleController(float x, float y, GradientColor gradient);
		ParticleController(float x, float y, string filename);
		ParticleController(float x, float y, string filename, int width, int height);
		//ParticleController(float x, float y, Texture texture);
		ParticleController(float x, float y, Tileset tileset);
		~ParticleController();

		virtual void init(float x, float y);

		void addParticle();
		void removeParticle(int index);

		Particle* particleAt(int index);

		//fairly obvious functions
		void setGradient(GradientColor gradient);
		void setColor(Color color);
		void setFile(string filename);
		void setFile(string filename, int width, int height);
		//void setTexture(Texture texture);
		void setTileset(Tileset tileset);
		void setSize(int width, int height);
		void setFade(bool setting);
		void setLifetime(float life);
		void setDirection(float angle);
		void setDirection(float angle, float margin);
		void setVelocity(float speed);
		void setVelocity(float speed, float acceleration);
		void setRotation(float rotation);
		void setRotation(float rotation, float margin);

		int getWidth();
		int getHeight();
		GradientColor getGradient();
		Color getColor();
		Color getColor(float time);
		int getCount();
		bool getFade();
		float getLifetime();
		float getDirection();
		float getVelocity();
		float getAcceleration();
		float getRotation();
		Vextor getDisplacement();

		virtual void update(float dt);
		virtual void render();
	};


	typedef boost::shared_ptr<ParticleController> pParticleController;
}

#endif