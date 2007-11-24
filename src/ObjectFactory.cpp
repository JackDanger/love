#include "ObjectFactory.h"
#include "AbstractImageDevice.h"
#include "AbstractSoundDevice.h"
#include "AbstractFileSystem.h"
#include "AbstractFile.h"
#include "Core.h"
#include "love.h"


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
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create the image
		pAbstractImage img(core->imaging->getImage(file));

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
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create the music
		pAbstractMusic music(core->audio->getMusic(file));

		// Load it.
		music->load();

		return music;

	}

	pAbstractSound ObjectFactory::newSound(const char * filename) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create the music
		pAbstractSound sound(core->audio->getSound(file));

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
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create the font
		pFont font(new Font(file, size));

		// Load it.
		font->load();

		return font;		
	}

	pAbstractFont ObjectFactory::newDefaultFont(int size) const
	{
		// Get a file pointer
		AbstractFile * file = core->filesystem->getBaseFile("data/fonts/FreeSans.ttf");

		// Create the font
		pFont font(new Font(file, size));

		// Load it.
		font->load();

		return font;		
	}

	pAbstractFont ObjectFactory::newImageFont(const char * filename, const char * glyphs) const
	{
		// Get the current source
		string source = core->current->getSource();

		// Get a file pointer
		AbstractFile * file = core->filesystem->getFile(source, string(filename));

		// Create the font
		pImageFont font(new ImageFont(file, string(glyphs)));

		// Load it
		font->load();

		return font;
	}

	pParticleSystem ObjectFactory::newParticleSystem() const
	{
		pParticleSystem psys(new ParticleSystem());

		return psys;
	}

	pBezier ObjectFactory::newBezier() const
	{
		pBezier b(new Bezier());
		return b;
	}

	pBezier ObjectFactory::newBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const
	{
		pBezier b(new Bezier());
		b->first(x1, y1, x2, y2, x3, y3, x4, y4);
		return b;
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
