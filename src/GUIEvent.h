#ifndef LOVE_GUI_EVENT_H
#define LOVE_GUI_EVENT_H

#include "Event.h"

#include <string>
#include <guichan.hpp>

using std::string;

namespace love
{

	/**
	* @class GUIEvent
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-10-15
	* @brief Passes GUI items about.
	**/
	class GUIEvent : public Event
	{
	private:

		gcn::Widget * source;
		string name;

	public:

		/**
		* @brief Contructs an empty GUIEvent.
		**/
		GUIEvent();

		GUIEvent(gcn::Widget * widget);

		virtual ~GUIEvent();

		/**
		* @brief Gets the widget.
		* @return widget
		**/
		gcn::Widget * getSource();

		/**
		* @brief Gets the widget name.
		* @return name
		**/
		const char * getName();

		/**
		* @brief Sets the widget.
		* @param widget
		**/
		void setSource(gcn::Widget * widget);

		/**
		* @brief Sets the widget name.
		* @param name
		**/
		void setName(string name);


	};

	typedef boost::shared_ptr<GUIEvent> pGUIEvent;

} // love

#endif
