/**
* @file Renderable.h
* @brief Contains definition of class Renderable.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_RENDERABLE_H
#define LOVE_RENDERABLE_H

#include "love_gl.h"

namespace love 
{

	/**
	* @class Renderable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Represents something that can be rendered.
	*
	* Everything that needs a visual representation should inherit from
	* this class.
	**/
	class Renderable
	{
	protected:

		bool visible;
		unsigned char opacity;

	public:
		
		virtual ~Renderable();

		/**
		* @brief Renders the object once.
		**/
		virtual void render() const;

		/**
		* @brief Returns whether or not the object is visible.
		* @return Whether or not the object is visible.
		**/
		bool isVisible();

		/**
		* @brief Sets the visibility of the object.
		* @param visible True for visible, false for invisible.
		**/
		void setVisible(bool visible);

		/**
		* @brief Gets the current opacity of the object.
		* @return The current opacity. 0 for invisible, 
		* 255 for completely opaque.
		**/
		unsigned char getOpacity();

		/**
		* @brief Sets a new opacity.
		* @param opacity The new opacity. (0-255)
		**/
		void setOpacity(unsigned char opacity);

	};


}// love

#endif
