%{
#include "using_graphics.h"
#include "love_defaults.h"
#include "resources.h"
%}

%inline %{

namespace love
{
	/**
	* Class definition.
	**/
	class ObjectFactory
	{
	public:
		
		pImage newImage(const char * filename)
		{
			pFile file(filesystem->newFile(game->getSource(), std::string(filename)));
			pImage img(graphics->newImage(file));
			img->load();
			return img;
		}
		
		pColor newColor(int r, int g, int b, int a = 255)
		{
			pColor c(new Color(r, g, b, a));
			return c;
		}
		
		pFont newFont(const char * filename, int size)
		{
			pFile file(filesystem->newFile(game->getSource(), std::string(filename)));
			pFont tmp(graphics->newFont(file, size));
			tmp->load();
			return tmp;
		}
		
		pFont newFont(int i, int size)
		{
			pFile file;
			
			if(i == LOVE_DEFAULT_FONT)
				file = Vera_ttf;
			
			pFont tmp(graphics->newFont(file, size));
			tmp->load();
			return tmp;
		}

		pFont newImageFont(const char * filename, const char * glyphs)
		{
			pFile file(filesystem->newFile(game->getSource(), std::string(filename)));
			pFont tmp(graphics->newImageFont(file, glyphs));
			tmp->load();
			return tmp;
		}
		
		pSound newSound(const char * filename)
		{
			pFile file(filesystem->newFile(game->getSource(), std::string(filename)));
			pSound tmp(audio->newSound(file));
			tmp->load();
			return tmp;			
		}
		
		pMusic newMusic(const char * filename)
		{
			pFile file(filesystem->newFile(game->getSource(), std::string(filename)));
			pMusic tmp(audio->newMusic(file));
			tmp->load();
			return tmp;		
		}
		
		pParticlesystem newParticlesystem()
		{
			pParticlesystem tmp = graphics->newParticlesystem();
			return tmp;
		}
		
		pAnimation newAnimation(const pImage * image)
		{
			pAnimation tmp(new Animation(*image));
			return tmp;
		}
		
		pAnimation newAnimation(const pImage * image, float fw, float fh, float delay, int num = 0)
		{
			pAnimation tmp(new Animation(*image, fw, fh, delay, num));
			return tmp;
		}
		
		
	};
	
	/**
	* Global "device".
	**/
	
	ObjectFactory objects;

} // LOVE

%}