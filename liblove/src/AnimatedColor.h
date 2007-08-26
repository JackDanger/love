#ifndef LOVE_ANIMATE_COLOR_H
#define LOVE_ANIMATE_COLOR_H

#include "Color.h"
#include "Container.h"

using std::vector;

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
		Container<Color> * globalColors;
		vector<Color *> colors;
		vector<float> times;
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
		AnimatedColor(Container<Color> * colors);

		/**
	 	 * @brief Does nothing.
	 	 **/
		~AnimatedColor();

		/**
		 * @param color A pointer to a Color object.
		 * @param time The amount of time associated with the color.
	 	 * @brief Adds a color to the color list. If this is the first color then it sets it as the current color.
	 	 **/
		void addColor(Color * color, float time);

		/**
		 * @param color The name of a color which is to be added.
		 * @param time The amount of time associated with the color.
	 	 * @brief Adds a color to the color list if it is found in the color Container.
	 	 **/
		void addColor(const char * color, float time);

		/**
		 * @return A Color object.
		 * @brief Creates a Color object of the current color.
		 **/
		Color getColor();

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

		virtual void setColor(float t);
	};

	typedef boost::shared_ptr<AnimatedColor> pAnimatedColor;
}

#endif
