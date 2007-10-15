#ifndef LOVE_ABSTRACT_GUI_H
#define LOVE_ABSTRACT_GUI_H

#include "AbstractImage.h"
#include "AbstractColor.h"
#include "Font.h"
#include "GUIText.h"
#include "Menu.h"
#include "Renderable.h"
#include "Updateable.h"
#include "EventListener.h"
#include "GUIEvent.h"
#include "DisplayModeListener.h"

#include <guichan.hpp>

namespace love
{
	class AbstractGUI : public gcn::ActionListener, public Initializable, public Renderable, public Updateable,
						public DisplayModeListener
	{
	protected:
		gcn::Gui * gui;
		gcn::Font * guifont;
		gcn::Graphics * graphics;
		gcn::ImageLoader * imageLoader;
		gcn::Container * top;

		pAbstractColor color;
		pAbstractFont font;
		GUIText * text;

	public:
		AbstractGUI();
		~AbstractGUI();

		virtual void action(const gcn::ActionEvent& actionEvent);

		/**
		 * @brief Adds a Menu to the gui.
		 * @param menu The Menu in question.
		 **/
		virtual void add(const pMenu * menu);

		/**
		 * @brief Adds a GUIchan Widget to the gui.
		 * @param widget The Widget in question.
		 **/
		virtual void add(gcn::Widget * widget);

		/**
		 * @brief Removes a Menu from the gui.
		 * @param widget The Menu in question.
		 **/
		virtual void remove(const pMenu * menu);

		/**
		 * @brief Removes a GUIchan Widget from the gui.
		 * @param widget The Widget in question.
		 **/
		virtual void remove(gcn::Widget * widget);

		/**
		 * @brief Clears the GUI of any elements.
		 **/
		virtual void clear();

		/**
		 * @brief Returns the default font.
		 * @return The default font used in the GUI system.
		 **/
		virtual pAbstractFont getFont();

		/**
		 * @brief Returns the default color.
		 * @return The default color used in the GUI system.
		 **/
		virtual pAbstractColor getColor();

		/**
		 * @brief Renders the GUI system.
		 **/
		void render();

		/**
		 * @brief Updates the GUI system.
		 * @param dt The time since last call (in seconds).
		 **/
		void update(float dt);
	};
}

#endif