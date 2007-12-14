#include "ObjectFactory.h"
#include "AbstractAudio.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "Core.h"
#include "love.h"

#include "OpenGLParticleSystem.h"

using std::string;

namespace love
{
	
	ObjectFactory::ObjectFactory()
	{
	}
	
	ObjectFactory::~ObjectFactory()
	{
	}
	
	pAbstractImage ObjectFactory::newImage(const char * filename) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		pAbstractFile file = core->filesystem->getFile(source, string(filename));

		// Create the image
		pAbstractImage img = core->graphics->getImage(file);

		// Load it.
		img->load();

		return img;
	}

	pFrameAnimation ObjectFactory::newAnimation(const pAbstractImage * image)
	{
		// Create the FrameAnimation
		pFrameAnimation fa(new FrameAnimation(*image));

		fa->load();

		return fa;
	}

	pFrameAnimation ObjectFactory::newAnimation(const pAbstractImage * image, int xFrames, int yFrames, int frameWidth, int frameHeight, float delay)
	{
		// Create the FrameAnimation
		pFrameAnimation fa(new FrameAnimation(*image));

		// Add quick frames.
		fa->addFrames(xFrames, yFrames, (float)frameWidth, (float)frameHeight, delay);

		fa->load();

		return fa;
	}

	pAbstractMusic ObjectFactory::newMusic(const char * filename) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		pAbstractFile file = core->filesystem->getFile(source, string(filename));

		// Create the music
		pAbstractMusic music = core->audio->getMusic(file); 

		// Load it.
		music->load();

		return music;

	}

	pAbstractSound ObjectFactory::newSound(const char * filename) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		pAbstractFile file = core->filesystem->getFile(source, string(filename));

		// Create the music
		pAbstractSound sound = core->audio->getSound(file);

		// Load it.
		sound->load();

		return sound;
	}

	pAbstractColor ObjectFactory::newColor(int r, int g, int b, int a) const
	{
		// Create the color
		pColor color(new Color(r, g, b, a));

		return color;
	}

	pAbstractColor ObjectFactory::newColor(int code, int a) const
	{
		// Create the color
		pColor color(new Color(code));
		color->setAlpha(a);

		return color;
	}

	pAbstractColor ObjectFactory::newAnimatedColor(int mode) const
	{
		// Create the color
		pAnimatedColor color(new AnimatedColor(mode));

		return color;
	}

	pAbstractFont ObjectFactory::newFont(const char * filename, int size) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		pAbstractFile file = core->filesystem->getFile(source, string(filename));

		// Create the font
		pAbstractFont font = core->graphics->getFont(file, size); //(new Font(file, size));

		// Load it.
		font->load();

		return font;		
	}

	pAbstractFont ObjectFactory::newDefaultFont(int size) const
	{
		// Create the font
		pAbstractFont font = core->graphics->getFont("data/fonts/Vera.ttf", size); //(new Font(file, size));

		// Load it.
		font->load();

		return font;		
	}

	pAbstractFont ObjectFactory::newImageFont(const char * filename, const char * glyphs) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		pAbstractFile file = core->filesystem->getFile(source, string(filename));

		// Create the font
		pAbstractFont font = core->graphics->getImageFont(file, glyphs);

		// Load it
		font->load();

		return font;
	}

	pParticleSystem ObjectFactory::newParticleSystem() const
	{
		pParticleSystem psys(new OpenGLParticleSystem());

		return psys;
	}

	pAbstractMenu ObjectFactory::newMenu(int type)
	{
		pMenu m(new Menu(core->gui->getFont(), core->gui->getColor(), type));
		//pMenu m(new Menu(core->graphics->getFont(), core->graphics->getColor(), type));
		m->show();

		//if(core->current->getGUI() != 0)
		//	core->current->getGUI()->add(m.get());
		return m;
	}

	pAbstractMenu ObjectFactory::newScrollMenu(int type)
	{
		pScrollMenu m(new ScrollMenu(core->gui->getFont(), core->gui->getColor(), type));
		//pMenu m(new Menu(core->graphics->getFont(), core->graphics->getColor(), type));
		m->show();

		//if(core->current->getGUI() != 0)
		//	core->current->getGUI()->add(m.get());
		return m;
	}

	pAbstractMenu ObjectFactory::newWindowMenu(int type, const char * caption)
	{
		pWindowMenu m(new WindowMenu(core->gui->getFont(), core->gui->getColor(), type));
		//pMenu m(new Menu(core->graphics->getFont(), core->graphics->getColor(), type));
		m->setCaption(caption);
		m->show();

		//if(core->current->getGUI() != 0)
		//	core->current->getGUI()->add(m.get());
		return m;
	}
	

} // love
