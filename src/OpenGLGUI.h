#ifndef LOVE_OPEN_GL_GUI_H
#define LOVE_OPEN_GL_GUI_H

#include "AbstractImage.h"
#include "AbstractColor.h"
#include "Font.h"
#include "GUIText.h"
#include "Menu.h"
#include "Renderable.h"
#include "Updateable.h"
#include "EventListener.h"
#include "DisplayModeListener.h"

#include <guichan.hpp>
#include <guichan/opengl.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

namespace love
{
	class OpenGLGUI : public gcn::ActionListener, public Renderable, public Updateable,
						public DisplayModeListener
	{
	private:
		gcn::Gui * gui;
		gcn::Font * guifont;
		gcn::OpenGLGraphics * graphics;
		gcn::OpenGLSDLImageLoader* imageLoader;
		gcn::Container * top;

		pAbstractColor color;
		pAbstractFont lovefont;
		GUIText * text;

	public:
		/**
		 * @brief Default constructor.
		 **/
		OpenGLGUI();

		/**
		 * @brief Deconstructor. Deletes pointers.
		 **/
		~OpenGLGUI();

		/**
		 * @brief Called whenever an ActionEvent occurs (like when a button is pressed).
		 * @param actionEvent A GUIChan ActionEvent object.
		 **/
		void action(const gcn::ActionEvent& actionEvent);

		/**
		 * @brief Adds a Menu to the gui.
		 * @param menu The Menu in question.
		 **/
		void add(pMenu menu);

		/**
		 * @brief Adds a GUIchan Widget to the gui.
		 * @param widget The Widget in question.
		 **/
		void add(gcn::Widget * widget);

		/**
		 * @brief Removes a GUIchan Widget from the gui.
		 * @param widget The Widget in question.
		 **/
		void remove(gcn::Widget * widget);

		/**
		 * @brief Clears the GUI of any elements.
		 **/
		void clear();

		/**
		 * @brief Returns the default font.
		 * @return The default font used in the GUI system.
		 **/
		pAbstractFont getFont();

		/**
		 * @brief Returns the default color.
		 * @return The default color used in the GUI system.
		 **/
		pAbstractColor getColor();

		/**
		 * @brief Creates and initializes the GUI system.
		 **/
		void init();

		/**
		 * @brief Renders the GUI system.
		 **/
		void render();

		/**
		 * @brief Updates the GUI system.
		 * @param dt The time since last call (in seconds).
		 **/
		void update(float dt);

		/**
		* @brief Called when the display mode changes.
		**/
		void displayModeChanged();
	};
}

#endif