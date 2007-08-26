/**
* @file GUICircleButton.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUICircleButton.
**/

#ifndef LOVE_GUICIRCLEBUTTON_H
#define LOVE_GUICIRCLEBUTTON_H

// LOVE
#include "GUIEntity.h"
#include "ImageFromFile.h"
#include "Font.h"
#include "Event.h"


// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class EventListener;
	class Mouse;

	/**
	* @class GUICircleButton
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GUICircleButton : public GUIEntity
	{
	private:

		friend class GUIGameListElement;

		AbstractImage * image;

		Font * font;

		string label;
		pEvent command;

		bool bg;

		bool enable;


	public:

		/**
		* @brief Contructs an empty GUICircleButton.
		**/
		GUICircleButton(AbstractImage * image, const string & label, pEvent command, Font * font = 0);
		virtual ~GUICircleButton();


		void setLabel(const string & label);

		void update(float dt);
		void render();

		int load();
		void unload();

		void mousePressed(float x, float y, int button);

	};

	typedef boost::shared_ptr<GUICircleButton> pGUICircleButton;

} // love

#endif

