#include "SplashScreen.h"
#include "FModinit.h"

namespace love
{

	SplashScreen::SplashScreen()
	{
	}

	SplashScreen::SplashScreen(string filename, float time)
	{
		this->image = new Tileset(filename, 1024, 1024);
		this->time = time;

		this->fadePortion = 1.0f/6.0f;

		this->fade = time * this->fadePortion;

		this->timeCount = 0;
		this->fadeCount = 0;

		this->soundwait = 0.6f;

		this->alpha = 0;
		this->wait = true;
		this->done = false;

		this->fadeDir = true;

		this->gc0 = new GradientColor(Color(0x000000), Color(0xffffff));
		this->gc1 = new GradientColor(Color(0x000000), Color(0xffffff));
		this->gc2 = new GradientColor(Color(0x000000), Color(0xffffff));
		this->gc3 = new GradientColor(Color(0x000000), Color(0xffffff));

		this->sound = new Sound();
		sound->load("data/splash.wav", FMOD_2D);

	}

	void SplashScreen::reset(float time)
	{
		this->time = time;

		this->fadePortion = 1.0f/6.0f;

		this->fade = time * this->fadePortion;

		this->timeCount = 0;
		this->fadeCount = 0;

		this->soundwait = 0.6f;

		this->alpha = 0;
		this->wait = true;
		this->done = false;

		this->fadeDir = true;		
	}

	SplashScreen::~SplashScreen()
	{
		delete sound;
	}

	void SplashScreen::render()
	{


		glEnable(GL_TEXTURE_2D);

		glLoadIdentity();

		image->bindTile(0);


		float t = (float)( 3 * (timeCount/time));

		glBegin(GL_QUADS);

			setColor(gc0, t);
			glTexCoord2f(0.0,0.0); glVertex2f(0,0);

			setColor(gc1, t + 0.1);
			glTexCoord2f(0.0,1.0); glVertex2f(0,1024);

			setColor(gc2, t + 0.2);
			glTexCoord2f(1.0,1.0); glVertex2f(1024,1024);

			setColor(gc3, t + 0.3);
			glTexCoord2f(1.0,0.0); glVertex2f(1024,0);	

		glEnd();

		glDisable(GL_TEXTURE_2D);
		

	}

	void SplashScreen::update(float dt)
	{
		
		// Play sound?
		soundwait -= dt;
		if(soundwait <= 1000.0f && soundwait <= 0)
		{
			soundwait = 1000000.0f;
			sound->play();
		}


		timeCount += dt;
		
		if(timeCount > time - time * this->fadePortion)
			wait = false;

		if(timeCount > time)
			done = true;

		if(fadeDir) // fade in
		{
			fadeCount += dt;
			alpha = 255/fade * fadeCount;

			if(alpha > 255)	alpha = 255;

			if(timeCount > fade)
			{
				fadeDir = false;
				fadeCount = 0;
			}


		}else // fade out
		{
			float noFadeTime = time * ( 1 - this->fadePortion );

			if(timeCount > noFadeTime)
			{
				fadeCount += dt;

				alpha = 255 - 255/fade * fadeCount;

				if(alpha < 0)
					alpha = 0;
			}
		}


	}

	bool SplashScreen::waiting()
	{
		return wait;
	}

	bool SplashScreen::isDone()
	{
		return done;
	}

	void SplashScreen::setColor(GradientColor * gc, float t)
	{

		if(t > 1)
			t = 1 - (t - 1);

		if(t < 0) t = 0;
		if(t > 1) t = 1;

		Color c = gc->getColor(t);

		glColor4ub(c.getRed(), c.getGreen(), c.getBlue(), this->alpha);
	}

}