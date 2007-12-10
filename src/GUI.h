#ifndef LOVE_GUI_H
#define LOVE_GUI_H

#include <guichan.hpp>

namespace love
{
	/**
	 * @class GUI
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-12-07
	 * @brief A wrapper class for the GUIchan Gui class to handle mouse-presses better.
	 **/
	class GUI : public gcn::Gui
	{
	protected:
		virtual void handleMousePressed(const gcn::MouseInput& mouseInput);
	public:
		GUI();
		~GUI();

		virtual bool hasFocus();
	};
}

#endif
