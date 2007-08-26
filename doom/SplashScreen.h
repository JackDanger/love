#ifndef LOVE_SPLASH_SCREEN
#define LOVE_SPLASH_SCREEN

#include "AbstractEntity.h"
#include "Tileset.h"
#include "GradientColor.h"

#include <string>

#include "Sound.h"

using std::string;


namespace love
{
	class SplashScreen : public AbstractEntity
	{
	private:

		Tileset * image;


		// All times in seconds

		float time;			// Total display time, including fading
		float timeCount;	// Elapsed Time

		float fade;			// Total fade time each "direction" (in/out)
		float fadeCount;	// Elapsed fade time for the current "direction"

		float fadePortion;

		float soundwait;

		bool fadeDir;

		float alpha;

		bool wait;

		bool done;

		GradientColor * gc0;
		GradientColor * gc1;
		GradientColor * gc2;
		GradientColor * gc3;

		Sound * sound;

	public:
		
		SplashScreen();
		SplashScreen(string filename, float time);
		~SplashScreen();

		void render();
		void update(float dt);

		bool waiting();
		bool isDone();

		void setColor(GradientColor * gc, float t);

		void reset(float time);
		

	};

	typedef boost::shared_ptr<SplashScreen> pSplashScreen;

}

#endif