#include "ParticleController.h"

namespace love
{
	ParticleController::ParticleController()
	{
		init(0,0);
	}

	ParticleController::ParticleController(float x, float y, Color color)
	{
		init(x,y);
		gradient = GradientColor(color, color);
	}

	ParticleController::ParticleController(float x, float y, GradientColor gradient)
	{
		init(x,y);
		this->gradient = gradient;
	}

	ParticleController::ParticleController(float x, float y, string filename)
	{
		init(x,y);
		tiles = new Tileset(filename, 32, 32);
	}

	ParticleController::ParticleController(float x, float y, string filename, int width, int height)
	{
		init(x,y);
		tiles = new Tileset(filename, width, height);

		this->width = width;
		this->height = height;
	}

	//ParticleController::ParticleController(float x, float y, Texture texture) {} //will come later

	ParticleController::ParticleController(float x, float y, Tileset tileset)
	{
		tiles = &tileset;
		
		this->width = tiles->getTileWidth();
		this->height = tiles->getTileHeight();
	}

	ParticleController::~ParticleController()
	{
		delete tiles;
	}

	void ParticleController::init(float x, float y)
	{
		setX(x);
		setY(y);

		gradient = GradientColor(0xFFFFFF, 0xFFFFFF);
		tiles = 0;

		width = 32;
		height = 32;

		fade = false;
	}

	void ParticleController::addParticle()
	{
		particles.push_back(Particle(this));
	}

	void ParticleController::removeParticle(int index)
	{
		particles.erase(particles.begin() + index);
	}

	Particle* ParticleController::particleAt(int index)
	{
		return &(particles[index]);
	}

	void ParticleController::setGradient(GradientColor gradient) { this->gradient = gradient; }
	void ParticleController::setColor(Color color) { gradient = GradientColor(color, color); }
	void ParticleController::setSize(int width, int height) { this->width = width; this->height = height; }
	void ParticleController::setFile(string filename) { tiles = new Tileset(filename, 32, 32); width = 32; height = 32; }
	void ParticleController::setFile(string filename, int width, int height) { tiles = new Tileset(filename, width, height); this->width = width; this->height = height; }
	//void setTexture(Texture texture) {}
	void ParticleController::setTileset(Tileset tileset) { tiles = &tileset; }
	void ParticleController::setFade(bool setting) { fade = setting; }
	void ParticleController::setLifetime(float life) { lifetime = life; }
	void ParticleController::setDirection(float angle) { direction = angle; directionMargin = 0; }
	void ParticleController::setDirection(float angle, float margin) { direction = angle; directionMargin = margin; }
	void ParticleController::setVelocity(float speed) { velocity = speed; acceleration = 0; }
	void ParticleController::setVelocity(float speed, float acceleration) { velocity = speed; this->acceleration = acceleration; }
	void ParticleController::setRotation(float rotation) { this->rotation = rotation; rotationMargin = 0; }
	void ParticleController::setRotation(float rotation, float margin) { this->rotation = rotation; rotationMargin = margin; }

	int ParticleController::getWidth() { return width; }
	int ParticleController::getHeight() { return height; }
	GradientColor ParticleController::getGradient() { return gradient; }
	Color ParticleController::getColor() { return gradient.getColor(0).getColor(); }
	Color ParticleController::getColor(float time) { return gradient.getColor(time / lifetime).getColor(); }
	int ParticleController::getCount(){ return (int)particles.size(); }
	bool ParticleController::getFade() { return fade; }
	float ParticleController::getLifetime() { return lifetime; }
	float ParticleController::getDirection()
	{
		float temp;

		for(int i = 0; i != 20; i++) { rand(); } //randomize it a little bit moar
		temp = (direction - (directionMargin / 2)) + (int)(directionMargin * rand() / (RAND_MAX + 1.0));

		return temp;
	}
	float ParticleController::getVelocity() { return velocity; }
	float ParticleController::getAcceleration() { return acceleration; }
	float ParticleController::getRotation()
	{
		float temp;

		for(int i = 0; i != 20; i++) { rand(); } //randomize it a little bit moar
		temp = (rotation - (rotationMargin / 2)) + (int)(rotationMargin * rand() / (RAND_MAX + 1.0));

		return temp;
	}
	Vextor ParticleController::getDisplacement()
	{
		float angle, tempdir, tempvel;
		tempdir = getDirection();
		tempvel = getVelocity();

		angle = (float)((tempdir - 90) * ((2 * 3.14159265358979323846) / 360));
		return Vextor( (tempvel * cos(angle)) , (tempvel * sin(angle)) );
	}

	void ParticleController::update(float dt)
	{

		for(int i = 0; i != particles.size(); i++)
		{
			if(particles[i].life >= lifetime) //remove a "dead" particle
			{
				removeParticle(i);
				i--;
			}
		}

		for(int i = 0; i != particles.size(); i++)
			particles[i].update(dt);
	}

	void ParticleController::render()
	{
		glEnable(GL_TEXTURE_2D);

		for(int i = 0; i != particles.size(); i++)
			particles[i].render();

		glDisable(GL_TEXTURE_2D);
	}
}