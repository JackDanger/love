/**
* @file FrameAnimation.h
* @brief Contains definition of class FrameAnimation.
* @date 2006-03-06
* @author Anders Ruud
**/

#ifndef LOVE_FRAME_ANIMATION_H
#define LOVE_FRAME_ANIMATION_H

// LOVE
#include "Sprite.h"
#include "AbstractImage.h"

// STL
#include <string>
#include <vector>

using std::vector;
using std::string;

namespace love
{

		
	
	

	/**
	* @class FrameAnimation
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-06
	* @brief Frame-by-frame animation.
	**/
	class FrameAnimation : public Sprite
	{

	public:

		/**
		* @struct frame
		* @version 1.0
		* @since 1.0
		* @author Anders Ruud
		* @date 2006-09-10
		* @brief Describes one frame.
		**/
		struct frame
		{
			float x;
			float y;
			float width;
			float height;

			float post_delay;
		};



	private:

		//
		AbstractImage * image;

		// Holds all the frames
		vector<frame> frames;

		// Start/stop
		bool running;

		// The current frame index
		unsigned int cfi;

		// Stores time that does not result in a frame change.
		float timeBuffer;

	public:
	
		/**
		* @brief Creates a new FrameAnimation.
		**/
		FrameAnimation();

		/**
		* @brief Creates a new FrameAnimation.
		* @param t The source Texture.
		**/
		FrameAnimation(AbstractImage * image);

		virtual ~FrameAnimation();


		/**
		* @brief Adds a frame to the 
		**/
		void addFrame(float x, float y, float width, float height, float post_delay);

		void addFrames(int sizex, int sizey, float width, float height, float post_delay);

		/**
		* @brief Starts the Animation.
		**/
		void start();

		/**
		* @brief Stops the Animation.
		**/
		void stop();

		/**
		* @brief Delays start of animation with t seconds.
		* @param t The number of seconds to delay.
		**/
		void delay(float t);

		virtual void bind();
		virtual void beginRender();
		virtual void sendVertices();
		virtual void endRender();

		virtual renderinfo getRenderInfo();
		virtual renderinfo getRenderInfo(float x, float y, float width, float height);
		

		/**
		* @brief Renders the current frame of the animation.
		**/
		void render();

		void render(float x, float y);

		void render(float x, float y, float width, float height);

		void renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

		/**
		* @brief Updates the animation. (Changes frame)
		* @param dt The time since last frame.
		**/
		void update(float dt);

		int load();

		void unload();
			

	};

	typedef boost::shared_ptr<FrameAnimation> pFrameAnimation;

}// love

#endif
