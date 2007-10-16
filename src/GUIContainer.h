#ifndef LOVE_GUI_CONTAINER_H
#define LOVE_GUI_CONTAINER_H

#include "Menu.h"

#include <guichan.hpp>

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

		void add(const pMenu * menu);
		void remove(const pMenu * menu);
	};
}

#endif
