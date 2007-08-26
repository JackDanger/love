/**
* @file Tile.h
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains definition for class Tile.
**/

#ifndef AMF_TILE_H
#define AMF_TILE_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love 
{

	/**
	* @class Tile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Represents a singe tile in the engine.
	*
	* Example usage:
	* @code Tile tile(10.0f, 20.0f, 3); @endcode
	* This would create a tile 10 px from the left, and 20 px from
	* the top, with id 3. This means the fourth tile in the Tileset.
	* @see Tileset
	* @todo: Make this into a struct? Can not derive this from Object due to memory problems.
	**/
	class Tile
	{
	private:

		// The tile's x position.
		float x;

		// The tile's y position.
		float y;

		// The tile's tileset id.
		int id;

	public:

		/**
		* This is the maximum number an unsigned short can hold, and it represents
		* an empty tile.
		**/
		static const int NULL_TILE = 0xffff;

		/**
		* @brief Creates a new Tile object.
		**/
		Tile();

		/**
		* @brief Creates a new Tile object
		* @param x The position of the tile along the x axis.
		* @param y The position of the tile along the x axis.
		* @param id The id of the tile (which array element this
		* tile is in a Tileset).
		* @see Tileset
		**/
		Tile(float x, float y, unsigned short id);

		virtual ~Tile();

		/**
		* @brief Checks the position of the tile.
		* @return The tile's position on the x-axis.
		**/
		float getX();

		/**
		* @brief Sets the position of the tile.
		* @param x The new position on the x axis.
		**/
		void setX(float x);

		/**
		* @brief Checks the position of the tile.
		* @return The tile's position on the y-axis.
		**/
		float getY();

		/**
		* @brief Sets the position of the tile.
		* @param y The new position on the y axis.
		**/
		void setY(float y);

		/**
		* @brief Checks the id of the tile.
		* @return The tile's id.
		**/
		unsigned short getId();

		/**
		* @brief Sets a new tile id.
		* @param id The tile's new id.
		**/
		void setId(unsigned short id);

	};

	typedef boost::shared_ptr<Tile> pTile;

}// love

#endif