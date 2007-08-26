#include "Particle.h"
#include "ParticleEmitter.h"

namespace love
{
	//private functions
	void Particle::accelerate(float time)
	{
		float vLength = displacement.normalize();
		float aLength = parent->getAcceleration() * time;

		float newLength = vLength + aLength;

		displacement *= newLength;
	}

	void Particle::rotate(float time)
	{
		rotation += (float)(rotationRate * ((2 * 3.14159265358979323846) / 360)) / time;
	}

	//public functions
	Particle::Particle()
	{
		parent = 0;
	}

	Particle::Particle(ParticleController * newParent)
	{
		parent = newParent;
		setPosition(parent->getX(),parent->getY());

		displacement = parent->getDisplacement();
		life = 0;
		rotationRate = parent->getRotation();
		rotation = (float)(rand() % 360);
		energy = 255;
	}

	Particle::~Particle()
	{}

	void Particle::update(float dt)
	{
		accelerate(dt);
		rotate(dt);

		move(displacement * dt);

		life += dt;

		if(parent->getFade())
		{
			float percentage = 1 - (life / parent->getLifetime());
			energy = percentage * 255; //255 = max energy
			if(energy < 0) energy = 0;
		}
	}

	void Particle::render()
	{
		glPushMatrix();

		int fag = parent->tiles->getTileWidth();

		if(parent->tiles != 0)
			parent->tiles->bindTile(0);
		glColor4ub(parent->getColor(life).getRed(),parent->getColor(life).getGreen(),parent->getColor(life).getBlue(),(GLubyte)energy);

		glTranslatef(getX(),getY(),0.0f);

		glRotatef(rotation,0.0f,0.0f,1.0f);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex2f(-((float)parent->getWidth() / 2), -((float)parent->getHeight() / 2));
			glTexCoord2f(0.0f,1.0f); glVertex2f(-((float)parent->getWidth() / 2), (float)parent->getHeight() / 2);
			glTexCoord2f(1.0f,1.0f); glVertex2f((float)parent->getWidth() / 2, (float)parent->getHeight() / 2);
			glTexCoord2f(1.0f,0.0f); glVertex2f((float)parent->getWidth() / 2, -((float)parent->getHeight() / 2));
		glEnd();

		glPopMatrix();
		
	}
}
