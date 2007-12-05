#ifndef LOVE_GUI_CONTAINER_H
#define LOVE_GUI_CONTAINER_H

#include "AbstractMenu.h"
#include "Menu.h"
#include "ScrollMenu.h"
#include "WindowMenu.h"

#include <guichan.hpp>
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	 * @class GUIContainer
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-10-16
	 * @brief Holds GUI items and can accept smart-pointers to Menu items.
	 **/
	class GUIContainer : public gcn::Container
	{
	protected:
	public:
		GUIContainer();
		~GUIContainer();

		virtual void add(const pAbstractMenu & menu);
		virtual void remove(const pAbstractMenu & menu);
	};

	typedef boost::shared_ptr<GUIContainer> pGUIContainer;
}

#endif
