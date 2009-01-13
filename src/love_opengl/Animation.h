/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* @author Anders Ruud
* @date 2008-01-19
**/

#ifndef LOVE_OPENGL_ANIMATION_H
#define LOVE_OPENGL_ANIMATION_H

// LOVE
#include "../liblove/graphics/Drawable.h"

// Module.
#include "Image.h"

// STD
#include <vector>

namespace love
{
namespace opengl
{

	// Represents a single frame.
	struct AnimationFrame
	{
		Image * image;
		int preDelay;  // Delay to previous frame.
		int postDelay; // Delay to next frame.
	};

	class Animation : public Drawable
	{
	private:

		// The source of the animation.
		Image * image;

		// Delays between frames.
		// delays[0] is the delay between frames[0] and frames[1].
		std::vector<float> delays;

		// Holds all the frames.
		std::vector<AnimationFrame> frames;

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
		Animation(Image * image);

		/**
		* Creates an Animation with frames from top-left to bottom right.
		* @param image The image to use as the source.
		* @param fw The width of each frame.
		* @param fh The height of each frame.
		* @param delay The delay after each frame.
		* @param num The number of frames. (0 = all)
		**/
		Animation(Image * image, float fw, float fh, float delay, int num = 0);

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
		void update(float dt);

		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;
	};

} // opengl
} // love

#endif // LOVE_OPENGL_ANIMATION_H
