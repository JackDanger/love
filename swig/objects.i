%{



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
			pFile file(filesystem->getFile(game->getSource(), std::string(filename)));
			pImage img(graphics->getImage(file));
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
			pFile file(filesystem->getFile(game->getSource(), std::string(filename)));
			pFont tmp(graphics->getFont(file, size));
			tmp->load();
			return tmp;
		}
		
		pSound newSound(const char * filename)
		{
			pFile file(filesystem->getFile(game->getSource(), std::string(filename)));
			pSound tmp(audio->getSound(file));
			tmp->load();
			return tmp;			
		}
		
		pMusic newMusic(const char * filename)
		{
			pFile file(filesystem->getFile(game->getSource(), std::string(filename)));
			pMusic tmp(audio->getMusic(file));
			tmp->load();
			return tmp;		
		}
		
		pParticlesystem newParticlesystem()
		{
			pParticlesystem tmp = graphics->getParticlesystem();
			return tmp;
		}
		
	};
	
	/**
	* Global "device".
	**/
	
	ObjectFactory objects;

} // LOVE

%}