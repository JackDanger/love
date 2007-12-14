#ifndef LOVE_ANIMATE_COLOR_H
#define LOVE_ANIMATE_COLOR_H

#include "AbstractColor.h"
#include "Container.h"

namespace love
{
	/**
	* @class AnimateColor
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-05-18
	* @brief A class for creating gradient colors.
	**/
	class AnimatedColor : public AbstractColor
	{
	protected:

		// Updated this to use pColor for great automatic cleanup pleasure.
		std::vector<pAbstractColor> colors;
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

		virtual float map(float t);

	public:
		const static int LOVE_ANIMATED_COLOR_LOOP = 1;
		const static int LOVE_ANIMATED_COLOR_PLAY_ONCE = 2;
		const static int LOVE_ANIMATED_COLOR_BOUNCE = 3;

		/**
		 * @param colors A pointer to a Container of colors.
	 	 * @brief Prepares for color animation, sets the mode to LOOP current color to black.
	 	 **/
		AnimatedColor(int mode = LOVE_ANIMATED_COLOR_LOOP);

		/**
	 	 * @brief Does nothing.
	 	 **/
		~AnimatedColor();

		/**
		 * @param color A pointer to a Color object.
		 * @param time The amount of time associated with the color.
	 	 * @brief Adds a color to the color list. If this is the first color then it sets it as the current color.
	 	 **/
		void addColor(const pAbstractColor * color, float time);

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
		pAbstractColor getColor();

		/**
		 * @param How much time to have passed (0 = no time, 1 = all time).
		 * @return A Color object.
		 * @brief Creates a Color object of the color.
		 **/
		pAbstractColor getColor(float time);

		/**
		 * @param mode The desired mode.
	 	 * @brief Sets the mode for the animator.
	 	 **/
		void setMode(int mode);

		/**
	 	 * @brief Starts the animator.
	 	 **/
		void play();

		/**
	 	 * @brief Stops the animator.
	 	 **/
		void stop();

		/**
	 	 * @brief Resets all variables.
	 	 **/
		void reset();

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Calls the appropriate function determined by the mode.
	 	 **/
		void update(float dt);

		/**
		 * @param t The time.
	 	 * @brief Sets the current color as the color which would occur at the passed time.
	 	 **/
		virtual void setColor(float t);
	};

	typedef boost::shared_ptr<AnimatedColor> pAnimatedColor;
}

#endif
