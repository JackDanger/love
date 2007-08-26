/**
* @file Tileset.h
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains definition for class Tileset.
**/

#ifndef TILESET_H
#define TILESET_H


#include <string>
using namespace std;

#include "Image.h"
#include "Object.h"


namespace love 
{


	class Image;

	/**
	* @class Tileset
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Represents a collection of tiles.
	*
	* Example usage:
	* @code Tileset tileset("mytileset.png",32,32); @endcode
	* This would create tiles of size 32 x 32 from the image 
	* "mytileset.png".
	*
	* Example of how to bind a tile for the use of rendering:
	* @code tileset.bindTile(0)  @endcode
	* This would bind the texture defined by the first tile in 
	* the Tileset.
	**/
	class Tileset : public Object
	{
	private:

		/**
		* If no tilesizes are specified in the constructor, 
		* this size is used.
		**/
		static const unsigned short DEFAULT_TILE_SIZE = 16;

		// Our image loader
		Image * image;

		// The dimension of this image, in tiles
		unsigned short width;
		unsigned short height;

		// How many tiles there are
		unsigned short size;

		// The tile dimensions
		unsigned short tileWidth;
		unsigned short tileHeight;

		// Holds the ints to the GL textures
		unsigned int * tiles;

		// This method performs the actual work.
		bool createTiles();

	public:
		
		/**
		* @brief Creates a new Tileset object.
		**/
		Tileset();

		/**
		* @brief Creates a new Tileset object based on the parameters.
		* @param image The image from which to create the tileset.
		* @param tileWidth The width of the tiles on this tileset. Defaults to 16.
		* @param tileHeight The height of the tiles on this tileset. Defaults to 16.
		**/
		Tileset(Image * image, unsigned short tileWidth = DEFAULT_TILE_SIZE, unsigned short tileHeight = DEFAULT_TILE_SIZE);

		/**
		* @brief Creates a new Tileset object based on the parameters.
		* @param filename The filename of the image from which to create the tileset.
		* @param tileWidth The width of the tiles on this tileset. Defaults to 16.
		* @param tileHeight The height of the tiles on this tileset. Defaults to 16.
		**/
		Tileset(string filename, unsigned short tileWidth = DEFAULT_TILE_SIZE, unsigned short tileHeight = DEFAULT_TILE_SIZE);
		
		/**
		* @brief Called when the object is deleted.
		**/
		virtual ~Tileset();
		
		/**
		* @brief Binds the texture ready for rendering.
		* @param id The id of the tile to bind.
		**/
		void bindTile(unsigned int id);

		/**
		* @brief Checks the number of tiles in this tileset.
		* @return The number of tiles.
		**/
		unsigned int getSize();

		/**
		* @brief Checks the size of the individual tile on this tileset.
		* @return The width of each tile.
		**/
		unsigned short getTileWidth();

		/**
		* @brief Checks the size of the individual tile on this tileset.
		* @return The height of each tile.
		**/
		unsigned short getTileHeight();

	};


} // love

#endif