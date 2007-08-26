/**
* @file GUIEntity.h
* @author Anders Ruud
* @date 2007-05-25
* @brief Contains definition for class GUIEntity.
**/

#ifndef LOVE_GUIENTITY_H
#define LOVE_GUIENTITY_H

// LOVE
#include "Entity.h"
#include "EventListener.h"
#include "MouseListener.h"
#include "KeyListener.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class GUIEntity
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-25
	* @brief 
	**/
	class GUIEntity : public Entity, public EventListener, public MouseListener, public KeyListener
	{
	protected:

		EventListener * parent;

		float width;
		float height;

	public:

		/**
		* @brief Contructs an empty GUIEntity.
		**/
		GUIEntity();
		virtual ~GUIEntity();

		void setParent(EventListener * parent);

		virtual void mousePressed(float x, float y, int button);
		virtual void mouseReleased(float x, float y, int button);
		virtual void eventFired(pEvent e);

		virtual void keyPressed(int key);
		virtual void keyReleased(int key);

		void setSize(float width, float height);


	};

	typedef boost::shared_ptr<GUIEntity> pGUIEntity;

} // love

#endif

