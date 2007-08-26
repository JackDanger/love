#include "ParticleEmitter.h"

namespace love
{
	//private functions
	void ParticleEmitter::init(float x, float y)
	{
		ParticleController::init(x,y);

		active = false;
		srand((unsigned)time(0));
		doRender = false;
	}

	//public functions
	ParticleEmitter::ParticleEmitter()
	{
		init(0,0);
	}

	ParticleEmitter::ParticleEmitter(float x, float y, Color color)
	{
		init(x,y);
		setColor(color);
	}

	ParticleEmitter::ParticleEmitter(float x, float y, GradientColor gradient)
	{
		init(x,y);
		setGradient(gradient);
	}

	ParticleEmitter::ParticleEmitter(float x, float y, string filename)
	{
		init(x,y);
		setFile(filename);
	}

	ParticleEmitter::ParticleEmitter(float x, float y, string filename, int width, int height)
	{
		init(x,y);
		setFile(filename, width, height);
	}

	ParticleEmitter::ParticleEmitter(float x, float y, Tileset tileset)
	{
		init(x,y);
		setTileset(tileset);
	}

	ParticleEmitter::~ParticleEmitter()
	{}

	void ParticleEmitter::start()
	{
		reloading = 0;
		active = true;
	}

	void ParticleEmitter::stop()
	{
		active = false;
	}

	void ParticleEmitter::update(float dt)
	{
		if(!active) return;

		ParticleController::update(dt);

		reloading += dt;

		if(reloading >= reloadRate) //make a new particles
		{
			for(int i = 0; i != ammunition; i++)
			{
				ParticleController::addParticle();
			}

			//reloading -= reloadRate;
			reloading = 0;
		}
	}

	void ParticleEmitter::render()
	{

		if(doRender)
		{
			glPushMatrix();
			glColor3ub(255,0,0);
			glBegin(GL_QUADS);
				glVertex2f(getX()-10,getY()+10);
				glVertex2f(getX()+10,getY()+10);
				glVertex2f(getX()+10,getY()-10);
				glVertex2f(getX()-10,getY()-10);
			glEnd();
			glPopMatrix();
		}

		ParticleController::render();
	}

	void ParticleEmitter::setAmmo(int ammo, float rate)
	{
		ammunition = ammo;
		reloadRate = rate;
	}

	float ParticleEmitter::getReloadRate() { return reloadRate; }
}
