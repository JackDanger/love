/**
* @file Viewport.h
* @brief Contains definition of class Viewport.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_VIEWPORT_H
#define LOVE_VIEWPORT_H


#include "Entity.h"

// Boost
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace love
{
	
	class Map;

	/**
	* @class Viewport
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Keeps track of the location and size of
	* the virtual camera.
	* @see Map
	**/
	class Viewport : public Entity
	{
	private:

		// Sync position.
		// The viewport will center it's view around 
		// this point on every update.
		float* xSync;
		float* ySync;

		// If this is false, we ignore the sync variables above.
		bool syncing;

		// The boundaries of the Viewport.
		// Currently disabled
		float xMax;
		float yMax;
		float xMin;
		float yMin;


		// The size of the viewport.
		// Typically the size of the rendering context.
		float width;
		float height;

		// The half of the variables above.
		// Saves some CPU in lookAt()
		float half_width;
		float half_height;

	public:

		/**
		* @brief Creates a new Viewport object.
		**/
		Viewport();

		/**
		* @brief Creates a new Viewport object.
		* @param x The x-coordinate of the starting point.
		* @param y The y-coordinate of the starting point.
		* @param xMax The max x-coordinate.
		* @param yMax The max y-coordinate.
		* @param width The width of the Viewport. Defaults to 1024.
		* @param height The height of the Viewport. Defaults to 800.
		**/ 
		Viewport(float x, float y, float xMax, float yMax, float width = 1024.0f, float height = 800.f);


		~Viewport();

		/**
		* @brief Updates the state of the Viewport.
		* @param dt The time since last frame.
		**/
		void update(float dt); 

		/**
		* @brief Returns the width of the Viewport.
		* @return The width of the Viewport. (Pixels)
		**/
		float getWidth();

		/**
		* @brief Returns the height of the Viewport.
		* @return The height of the Viewport. (Pixels)
		**/
		float getHeight();

		/**
		* @brief Translates everything based on the Viewport's
		* position. (Using glTranslatef).
		*
		* This can no longer be generally used, due to more advanced
		* scrolling behaviour in some components.
		**/
		void translate();

		/**
		* @brief Sets the position to (0,0)
		**/
		void reset();

		/**
		* @brief Sets the constraints of the Viewport.
		* @param xMin The minimum x position.
		* @param xMax The maximum x position.
		* @param yMin The minimum y position.
		* @param yMax The maximum y position.
		**/
		void setConstraints(float xMin, float xMax, float yMin, float yMax);

		/**
		* @brief Sets a point that the Viewport should sync with.
		* @param xSync The x coordinate of the point.
		* @param ySync The y coordinate of the point.
		*
		* Using this method causes the Viewport to constantly call 
		* lookAt using values found in the supplied pointers. (Constantly
		* beeing every time update is called).
		* @see update(float dt);
		* @see lookAt(float x, float y);
		**/
		void sync(float* xSync, float* ySync);

		/**
		* @brief Disables the behaviour enabled in sync().
		* @see sync(float* xSync, float* ySync)
		**/
		void deSync();

		/**
		* @brief Causes the Viewport to look at a certain point.
		* @param x The x coordinate.
		* @param y The y coordinate.
		*
		* This point will be in the center of the viewport after this
		* method has finished.
		**/
		void lookAt(float x, float y);

	};

	typedef boost::shared_ptr<Viewport> pViewport;

}// love

#endif