/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_ANIMATION_H
#define LOVE_OPENGL_ANIMATION_H


// LOVE
#include <love/constants.h>

// Module.
#include "Sprite.h"
#include "Image.h"

// STD
#include <vector>

namespace love_opengl
{

	// Represents a single frame.
	struct frame
	{
		float texels[8];
		float vertices[8];
		float x, y, width, height;
		int pre_delay; // Delay to previous frame.
		int post_delay; // Delay to next frame.
	};

	/**
	* A class for creating frame-by-frame animations.
	*
	* @author Anders Ruud
	* @date 2008-01-19
	**/
	class Animation : public Sprite
	{
	private:

		// The source of the animation.
		pImage image;

		// Delays between frames.
		// delays[0] is the delay between frames[0] and frames[1].
		std::vector<float> delays;

		// Holds all the frames.
		std::vector<frame> frames;

		// Animation mode.
		int mode;

		// The current frame.
		int current;
	
		// True if playing, false otherwise.
		bool playing;

		// "Left over"-time.
		float timeBuffer;

		// Used for bounce mode.
		int direction;

		// Overall speed. (1 = normal).
		float speed;

	public:

		/**
		* Creates an Animation with no frames.
		* @param image The image to use as the source.
		**/
		Animation(pImage image);

		/**
		* Creates an Animation with frames from top-left to bottom right.
		* @param image The image to use as the source.
		* @param fw The width of each frame.
		* @param fh The height of each frame.
		* @param delay The delay after each frame.
		* @param num The number of frames. (0 = all)
		**/
		Animation(pImage image, float fw, float fh, float delay, int num = 0);

		virtual ~Animation();

		/**
		* Adds a single frame.
		* @param x The top-left corner of the frame.
		* @param y The top-right corner of the frame.
		* @param w The width of the frame.
		* @param h The height of the frame.
		* @param delay The delay after the frame.
		**/
		void addFrame(float x, float y, float w, float h, float delay);

		/**
		* Sets the current animation mode, and reset.
		**/
		void setMode(int mode);

		/**
		* Causes the Animation to start playing.
		**/
		void play();

		/**
		* Causes the Animation to stop.
		**/
		void stop();

		/**
		* Resets the Animation.
		**/
		void reset();

		/**
		* Resets timebuffers, and sets the current frame directly.
		**/
		void seek(int frame);

		/**
		* Gets the current frame.
		**/
		int getCurrentFrame() const;

		/**
		* Gets amount of frames.
		**/
		int getSize() const;

		/**
		* Sets the delay after a frame.
		**/
		void setDelay(int frame, float delay);

		/**
		* Sets the overall animation speed.
		**/
		void setSpeed(float speed);

		/**
		* Gets the overall animation speed.
		**/
		float getSpeed() const;

		// From Sprite
		void bind() const;
		void update(float dt);

		void draw(float x, float y) const;
		void draw(float x, float y, float angle, float sx, float sy, int flip) const;

	};

	typedef boost::shared_ptr<Animation> pAnimation;

} // love_opengl

#endif // LOVE_OPENGL_ANIMATION_H
