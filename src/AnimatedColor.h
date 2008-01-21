/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_ANIMATED_COLOR_H
#define LOVE_ANIMATED_COLOR_H

// LOVE
#include "Color.h"

// STD
#include <vector>

namespace love
{

	// Animation modes.
	enum
	{
		LOVE_ANIMATED_COLOR_LOOP = 1,
		LOVE_ANIMATED_COLOR_PLAY_ONCE,
		LOVE_ANIMATED_COLOR_BOUNCE
	};

	/**
	* A class for creating gradient colors.
	*
	* @author Michael Enger
	* @date 2007-05-18
	**/
	class AnimatedColor : public Color
	{
	protected:

		std::vector<Color> colors;
		std::vector<float> times;
		float total; //the maximum time requried to gradient through the colors
		float elapsed; //the amount of time that has passed
		int mode;
		bool active;
		bool direction; //only used for bounce mode (true = right way, false = "wrong" way)

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Updates the current color in accordance to the amount of time that has passed and loops the list.
	 	 **/
		void loop(float dt);

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Updates the current color in accordance to the amount of time that has passed and stops on the last color.
	 	 **/
		void play_once(float dt);

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Updates the current color in accordance to the amount of time that has passed and bounces back and forth between the colors.
	 	 **/
		void bounce(float dt);

	public:

		/**
		 * @param colors A pointer to a Container of colors.
	 	 * @brief Prepares for color animation, sets the mode to LOOP current color to black.
	 	 **/
		AnimatedColor(int mode = LOVE_ANIMATED_COLOR_LOOP);

		virtual ~AnimatedColor();

		/**
		 * @param color A pointer to a Color object.
		 * @param time The amount of time associated with the color.
	 	 * @brief Adds a color to the color list. If this is the first color then it sets it as the current color.
	 	 **/
		void addColor(const pColor & color, float time);

		/**
		* @brief Adds a color directly.
		* @param r The red color component.
		* @param g The green color component.
		* @param b The blue color component.
		* @param a The alpha component.
		* @param time The amount of time associated with the color.
		**/
		void addColor(int r, int g, int b, int a, float time);

		/**
		 * @return A Color object.
		 * @brief Creates a Color object of the current color.
		 **/
		pColor getColor();

		/**
		 * @param How much time to have passed (0 = no time, 1 = all time).
		 * @return A Color object.
		 * @brief Creates a Color object of the color.
		 **/
		pColor getColor(float time);

		/**
		 * @param mode The desired mode.
	 	 * @brief Sets the mode for the animator.
	 	 **/
		void setMode(int mode);

		/**
	 	 * Starts the animator.
	 	 **/
		void play();

		/**
	 	 * Stops the animator.
	 	 **/
		void stop();

		/**
	 	 * Resets all variables.
	 	 **/
		void reset();

		/**
		 * Calls the appropriate function determined by the mode.
	 	 **/
		void update(float dt);

	};

	typedef boost::shared_ptr<AnimatedColor> pAnimatedColor;
}

#endif
