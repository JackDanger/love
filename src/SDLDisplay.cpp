#include "SDLDisplay.h"

// LOVE
#include "love_version.h"
#include "OpenGLGraphics.h"
#include "using_gl.h"

// STD
#include <sstream>

namespace love
{
	
	SDLDisplay::~SDLDisplay()
	{
		quit();
	}

	bool SDLDisplay::init(int argc, char* argv[])
	{
	
		// Try to init SDL_video subsystem
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{
			printf("Could not init SDL_VIDEO: %s\n", SDL_GetError());
			return false;
		}

		// Get the video info 
		video = SDL_GetVideoInfo();

		if(!video)
		{
			printf("Could not get video information: %s\n", SDL_GetError());
			return false;
		}

		// Set caption
		std::string title = "LOVE ";
		title += version_string();
		SDL_WM_SetCaption(title.c_str(), 0);

		return true;
	}

	void SDLDisplay::quit()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);		
	}

	int SDLDisplay::isSupported(const display_mode & dm)
	{

		Uint32 sdlflags = dm.fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Check if mode is supported
		int bpp = SDL_VideoModeOK(dm.width, dm.height, dm.color_depth, sdlflags);

		if(bpp == 0)
		{
			printf("Video mode is not supported.");
			return -1;
		}

		// Check if mode is supported
		if(bpp == dm.color_depth)
			return 0;

		// Otherwise, return the color depth
		return bpp;
	}

	int SDLDisplay::tryChange(const display_mode & dm)
	{

		// Set GL attributes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		//SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, (dm.vsync ? 1 : 0));
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 0);

		// FSAA
		if(dm.fsaa > 0)
		{
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, dm.fsaa ) ;
		}

		// Fullscreen?
		Uint32 sdlflags = dm.fullscreen ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;


		// Have SDL set the video mode.
		if(SDL_SetVideoMode(dm.width, dm.height, dm.color_depth, sdlflags ) == 0)
		{
			printf("Could not set video mode: %s\n", SDL_GetError());
			return 1;
		}

		// Check if FSAA failed or not
		if(dm.fsaa > 0)
		{
			int buffers;
			int samples;

			glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & buffers ) ;
			glGetIntegerv( GL_SAMPLES_ARB, & samples ) ;

			// Don't fail because of this, but issue a warning.
			if ( ! buffers || (samples != dm.fsaa))
				printf("Warning, quality setting failed! (Result: buffers: %i, samples: %i)\n", buffers, samples);
		}

		
		// Okay, setup OpenGL here, for now.

		// Enable blending
		glEnable(GL_BLEND);

		// "Normal" blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable line smoothing.
		glEnable (GL_LINE_SMOOTH);
		glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);

		// Cull backface
		glEnable(GL_CULL_FACE);		// Enable face culling (no need to render surfaces we can't see
		glCullFace(GL_BACK);		// Do not render back face.

		// Set the background color
		glClearColor( 0.0, 0.0, 0.0, 0.0 );

		// Enable textures
		glEnable(GL_TEXTURE_2D);	

		// Set the viewport to top-left corner
		glViewport(0,0, dm.width, dm.height);

		// Reset the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up orthographic view (no depth)
		glOrtho(0.0, dm.width,dm.height,0.0, -1.0, 1.0);

		// Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set the new display mode as the current display mode
		current = dm;

		return 0;

	}

	Graphics * SDLDisplay::newGraphics() const
	{
		return new OpenGLGraphics();
	}

	void SDLDisplay::setTitle(const std::string & title) const
	{
		SDL_WM_SetCaption(title.c_str(), 0);
	}

}// love
