#include "SDLDisplay.h"
#include "love.h"
#include "DisplayModeListener.h"
#include "OpenGLGraphics.h"

#include "SDL/SDL.h"
#include "GLee.h"
#include "SDL/SDL_opengl.h"
#include "SDL_image.h"

#include <sstream>
#include <string>

using std::stringstream;
using std::string;

namespace love
{

	SDLDisplay::SDLDisplay()
	{
	}

	SDLDisplay::~SDLDisplay()
	{
	}

	int SDLDisplay::init()
	{
	
		// Try to init SDL_video subsystem
		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
		{
			printf("Could not init SDL_VIDEO: %s\n", SDL_GetError());
			return LOVE_ERROR;
		}

		// Get the video info 
		video = SDL_GetVideoInfo();

		if(!video)
		{
			printf("Could not get video information: %s\n", SDL_GetError());
			return LOVE_ERROR;
		}

		// Set caption
		SDL_WM_SetCaption(makeCaption().c_str(), 0);

		// Set window icon.
		//SDL_Surface* icon = IMG_Load("love16x16.png");
		//SDL_WM_SetIcon(icon, NULL);

		return LOVE_OK;
	}

	int SDLDisplay::isSupported(DisplayMode displayMode)
	{

		Uint32 sdlflags = displayMode.isFullscreen() ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;

		// Check if mode is supported
		int bpp = SDL_VideoModeOK(displayMode.getWidth(), displayMode.getHeight(), displayMode.getColorDepth(), sdlflags);

		if(bpp == 0)
		{
			printf("Video mode is not supported.");
			return LOVE_ERROR;
		}

		// Check if mode is supported
		if(bpp == displayMode.getColorDepth())
			return LOVE_OK;

		// Otherwise, return the color depth
		return bpp;
	}

	int SDLDisplay::tryChange(DisplayMode displayMode)
	{

		// Set GL attributes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, (displayMode.isFullscreen() ? 1 : 0));

		// FSAA
		if(displayMode.getFSAA() > 0)
		{
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) ;
			SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, displayMode.getFSAA() ) ;
		}

		// Fullscreen?
		Uint32 sdlflags = displayMode.isFullscreen() ? (SDL_OPENGL | SDL_FULLSCREEN) : SDL_OPENGL;


		// Have SDL set the video mode.
		if(SDL_SetVideoMode(displayMode.getWidth(), displayMode.getHeight(), displayMode.getColorDepth(), sdlflags ) == 0)
		{
			printf("Could not set video mode: %s\n", SDL_GetError());
			return LOVE_ERROR;
		}

		// Check if FSAA failed or not
		if(displayMode.getFSAA() > 0)
		{
			int buffers;
			int samples;

			glGetIntegerv( GL_SAMPLE_BUFFERS_ARB, & buffers ) ;
			glGetIntegerv( GL_SAMPLES_ARB, & samples ) ;

			// Don't fail because of this, but issue a warning.
			if ( ! buffers || (samples != displayMode.getFSAA()))
				printf("Warning, quality setting failed! (Result: buffers: %i, samples: %i)\n", buffers, samples);
		}

		
		// Okay, setup OpenGL here, for now.

		// Enable blending
		glEnable(GL_BLEND);		

		// "Normal" blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Cull backface
		glEnable(GL_CULL_FACE);		// Enable face culling (no need to render surfaces we can't see
		glCullFace(GL_BACK);		// Do not render back face.

		// Set the background color
		glClearColor( 0.0, 0.0, 0.0, 0.0 );

		// Enable textures
		glEnable(GL_TEXTURE_2D);	

		// Set the viewport to top-left corner
		glViewport(0,0, displayMode.getWidth(), displayMode.getHeight());

		// Reset the projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up orthographic view (no depth)
		glOrtho(0.0, displayMode.getWidth(),displayMode.getHeight(),0.0, -1.0, 1.0);

		// Reset modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Set the new display mode as the current display mode
		currentDisplayMode = displayMode;

		// Let the listener know that we changed mode
		if(listener != 0) 
			listener->displayModeChanged();

		return LOVE_OK;

	}


	AbstractGraphics * SDLDisplay::getGraphics() const
	{
		return new OpenGLGraphics();
	}

	int SDLDisplay::getWidth() const
	{
		return currentDisplayMode.getWidth();
	}

	int SDLDisplay::getHeight() const
	{
		return currentDisplayMode.getHeight();
	}

	std::string SDLDisplay::makeCaption() const
	{
		// Create caption
		stringstream s;
		s << "LOVE ";
		s << LOVE_MAJOR_VERSION;
		s << ".";
		s << LOVE_MINOR_VERSION;
		s << ".";
		s << LOVE_REVISION;
		s << "b";
		
		return s.str();
	}


}// love
