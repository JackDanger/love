#ifndef LOVE_OPEN_GL_GUI_H
#define LOVE_OPEN_GL_GUI_H

#include "AbstractImage.h"
#include "AbstractColor.h"
#include "Font.h"
#include "GUIText.h"
#include "Menu.h"
#include "Renderable.h"
#include "Updateable.h"

#include <guichan.hpp>
#include <guichan/opengl.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>

namespace love
{
	class OpenGLGUI : public gcn::ActionListener, public Renderable, public Updateable
	{
	private:
		gcn::Gui * gui;
		gcn::Font * guifont;
		gcn::OpenGLGraphics * graphics;
		gcn::OpenGLSDLImageLoader* imageLoader;
		gcn::Container * top;
		AbstractColor * color;
		AbstractFont * lovefont;
		AbstractColor * lovecolor;
		GUIText * text;

		// the default error/warning messages
		Menu * error;
		AbstractImage * errorBackground;
		AbstractImage * errorWarning;
		AbstractImage * errorError;

	public:
		OpenGLGUI();
		~OpenGLGUI();

		void showError(const char * text);
		void showWarning(const char * text);

		void action(const gcn::ActionEvent& actionEvent);

		void init();
		void render();
		void update(float dt);
	};
}

#endif