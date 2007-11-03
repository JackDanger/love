#include "Console.h"

#include "Font.h"
#include "love.h"
#include "Core.h"
#include "AbstractFileSystem.h"
#include "AbstractDisplay.h"
#include "DisplayMode.h"
#include <sstream>
#include "Timer.h"

namespace love
{
	
	Console::Console(int size) : compact(true), visible(false), font(0), size(size)
	{
	}
	
	Console::~Console()
	{
	}

	void Console::update(float dt)
	{
	}

	void Console::render()
	{

		float th = 10;
		const DisplayMode & dm = core->display->getCurrentDisplayMode();
		float height = (float)messages.size() * (th);
		float dh = (float)dm.getHeight();
		float dw = (float)dm.getWidth();

		

		if(compact)
			height = 10;




		glLoadIdentity();

		glDisable(GL_TEXTURE_2D);

		glColor4ub(0, 0, 0, 150);

		glBegin(GL_QUADS);

		glVertex2f(0, dh-height-(2*th));
		glVertex2f(0, dh);
		glVertex2f(dw, dh );
		glVertex2f(dw, dh-height-(2*th));
		glEnd();

		glEnable(GL_TEXTURE_2D);


		if(compact)
		{
			glPushMatrix();
			glColor4ub(255, 255, 255, 200);

			glPushMatrix();
			glTranslatef(th, dh - height, 0);

			std::stringstream version;
			version << LOVE_MAJOR_VERSION;
			version << ".";
			version << LOVE_MINOR_VERSION;
			version << ".";
			version << LOVE_REVISION;
			
			font->print("LOVE " + version.str());
			glPopMatrix();	

			glPushMatrix();
			glTranslatef(dw - 50, dh - height, 0);

			std::stringstream fps;
			fps << core->timer->getFps();
			
			font->print("FPS: " + fps.str());
			glPopMatrix();	


			glPopMatrix();	
			return;
		}



		glPushMatrix();
		glColor4ub(255, 255, 255, 200);

		glTranslatef(th, dh-th, 0);

		for(unsigned int i =0;i<messages.size();i++)
		{
			string s = messages[i];
			font->print(s);
			glTranslatef(0, -th, 0);
		}

		glPopMatrix();




	

	}

	int Console::load()
	{

		if(!font)
			delete font;

		// Get a reference to the filesystem
		const AbstractFileSystem & fs = core->getFilesystem();

		font = new Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 7);

		return (font->load());
	}

	void Console::unload()
	{
		font->unload();
	}

	void Console::push(string message)
	{
		messages.push_front(message);

		if(messages.size() > (unsigned int)size) messages.pop_back();
	}

	
} // love
