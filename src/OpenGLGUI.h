#ifndef LOVE_OPEN_GL_GUI_H
#define LOVE_OPEN_GL_GUI_H

#include "AbstractGUI.h"

#include <guichan/opengl.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

// 100% quick and dirty love graphics output object.
#include "gcn/lovegraphics.hpp"

namespace love
{

	

	class OpenGLGUI : public AbstractGUI
	{
	protected:

		gcn::LOVEGraphics * graphics;

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
		 * @brief Creates and initializes the GUI system.
		 **/
		int init();

		/**
		* @brief Called when the display mode changes.
		**/
		void displayModeChanged();
	};
}

#endif

