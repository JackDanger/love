/**
* @file StateAnimation.h
* @brief Contains definition of class StateAnimation.
* @date 2006-03-17
* @author Anders Ruud
**/

#ifndef LOVE_STATE_ANIMATION_H
#define LOVE_STATE_ANIMATION_H

#include "Animation.h"
#include "FrameAnimation.h"
#include <vector>

using namespace std;

namespace love
{


	/**
	* @class StateAnimation
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-17
	* @brief A collection of serveral FrameAnimations.
	*
	* The idea is that you quickly can change between the different
	* animations stored here. This way we can represent movement in different
	* directions, spawning, death and so forth.
	* @see FrameAnimation
	**/
	class StateAnimation : public Animation
	{

	private:

		// Pointer to the current animation.
		FrameAnimation * currentAnim;

		// This vector holds all the FrameAnimations
		vector<FrameAnimation> animations;

	public:
	
		/**
		* @brief Creates a new StateAnimation.
		**/
		StateAnimation();

		virtual ~StateAnimation();

		/**
		* @brief Renders the current animation.
		**/
		void render();

		/**
		* @brief Updates the animation. (Changes frame)
		* @param dt The time since last frame.
		**/
		void update(float dt);
			

	};

	typedef boost::shared_ptr<StateAnimation> pStateAnimation;

}// love

#endif