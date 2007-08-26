#include "Tileset.h"


#include "love_gl.h"


/**
* AWHOOOOGHA!1!!11 There's a memory leak somewhere in this file. 
* TODO: FIX
**/

namespace love
{

	Tileset::Tileset()
	{
	}

	/**
	* Creates a tileset from the given image and tile dimensions.
	**/
	Tileset::Tileset(Image * image, unsigned short tileWidth, unsigned short tileHeight)
	{
		// Assign member variables
		this->image			= image;
		this->tileWidth		= tileWidth;
		this->tileHeight	= tileHeight;
		
		createTiles();
	}

	/**
	* Creates a tileset from a filename directly.
	**/
	Tileset::Tileset(string filename, unsigned short tileWidth, unsigned short tileHeight)
	{

		// Assign member variables
		this->image			= new Image(filename);
		this->image->load();

		this->tileWidth		= tileWidth;
		this->tileHeight	= tileHeight;
		
		createTiles();
		
	}


	Tileset::~Tileset()
	{
		tiles = 0;
		delete [] tiles;
		delete image;
	}

	/**
	* This method does all the work in this class.
	* It calculates the number of possible tiles on the 
	* supplied image, extracts them, and assigns them 
	* to textures.
	*
	* TODO: Check if tile creation is possible.
	**/
	bool Tileset::createTiles()
	{

		// Calculates the number of tiles on this tileset.
		this->height	= (unsigned short)(image->getHeight() / tileHeight);
		this->width		= (unsigned short)(image->getWidth() / tileWidth);			
		this->size		= this->width * this->height;

		// Allocate memory for the tiles.
		this->tiles		= new unsigned int[this->size];

		// Generate texture objects.
		glGenTextures(this->size,tiles);

		// This block creates the actual GL textures.
		for(unsigned short i = 0;i<this->size;i++)
		{
			// We need to cut out a small piece of a larger image.
			// These two lines calculate the top left corner of where
			// we need to start our cropping.
			unsigned int x = (i%width)*tileWidth;
			unsigned int y = (unsigned int)(i/width)*tileHeight;

			// Sets up the texture.
			// (Whatever we do from here to next glBind will affect
			// the texture at tiles[i]).
			glBindTexture(GL_TEXTURE_2D, tiles[i]);

			// How to filter when resized.
			// We will not be doing too much resizing. 
			// GL_NEAREST produces a zoom-effect rather than an interpolated 
			// resize. (And so we maintain the pixel-ness).
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			// Assign the actual texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tileWidth, 
				tileHeight, 0, image->getFormat(), GL_UNSIGNED_BYTE,image->getPixels(x, y, tileWidth, tileHeight));

		}


		return true;
	}


	/**
	* Binds a texture by tile id.
	**/
	void Tileset::bindTile(unsigned int id)
	{
		// Only bind if it exists
		if(id < this->size)
			glBindTexture(GL_TEXTURE_2D, tiles[id]);
	}

	unsigned int Tileset::getSize()
	{
		return this->size;
	}

	unsigned short Tileset::getTileWidth()
	{
		return this->tileWidth;
	}

	unsigned short Tileset::getTileHeight()
	{
		return this->tileHeight;
	}

}// love