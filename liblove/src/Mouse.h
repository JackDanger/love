/**
* @file Mouse.h
* @author Anders Ruud
* @date 2006-12-01
* @brief Contains definition for class Mouse.
**/

#ifndef LOVE_MOUSE_H
#define LOVE_MOUSE_H

// LOVE
#include "love_mouse.h"
#include "MouseListener.h"
#include "MouseMotionListener.h"
#include "AbstractDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Mouse
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-12-01
	* @brief 
	**/
	class Mouse : public AbstractDevice, public MouseListener, public MouseMotionListener
	{
	private:

		// buttons
		int buttons;

		// x
		float x;

		// y
		float y;

		// 
		bool visible;


	public:

		/**
		* @brief Contructs an empty Mouse.
		**/
		Mouse();
		virtual ~Mouse();



		/**
		* @brief Inits the mouse.
		**/
		int init();

		/**
		* @brief Gets buttons.
		* @return buttons.
		**/
		int getButtons() const;


		/**
		* @brief Sets buttons.
		* @param buttons 
		**/
		void setButtons(int buttons);


		/**
		* @brief Gets x.
		* @return x.
		**/
		float getX() const;


		/**
		* @brief Sets x.
		* @param x 
		**/
		void setX(float x);


		/**
		* @brief Gets y.
		* @return y.
		**/
		float getY() const;


		/**
		* @brief Sets y.
		* @param y 
		**/
		void setY(float y);

		/**
		* 
		* 
		**/
		void mousePressed(float x, float y, int state);

		/**
		* 
		* 
		**/
		void mouseReleased(float x, float y, int state);

		void mouseMoved(float x, float y);


		void setVisible(bool visible);
		bool isVisible() const;

		bool isDown(int button) const;


	};

	typedef boost::shared_ptr<Mouse> pMouse;

} // love

#endif

