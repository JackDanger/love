/**
* @file Map.h
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains definition for class Map.
**/

#ifndef LOVE_MAP_H
#define LOVE_MAP_H

#include <vector>

#include "AbstractEntity.h"
#include "TileLayer.h"

using namespace std;

namespace love
{

	class Viewport;

	/**
	* @class Map
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-01-15
	* @brief Represents an entire level.
	**/
	class Map : public AbstractEntity
	{
	private:

		// The layers on this map
		vector<TileLayer> tileLayers;

		// The current viewport
		Viewport * viewport;
		

		/**
		* @brief Sets Viewport limits based on the biggest
		* tileLayer.
		**/
		void restrainViewport();

	public:

		const static unsigned int FORMAT_TILED = 0;

		/**
		* @brief Creates a new Map object.
		**/
		Map();

		virtual ~Map();

		/**
		* @brief Renders a map and it's components.
		**/
		void render();

		/**
		* @brief Updates the state of the map. 
		**/
		void update(float dt);

		/**
		* @brief Loads a map.
		* @param filename The file from which to load the map.
		* This function autodetects the filetype based on the
		* extension.
		* @todo Create.
		**/
		bool load(string filename);

		/**
		* @brief Loads a map.
		* @param filename The file from which to load the map.
		* @param float Which fileformat we're dealing with.
		**/
		bool load(string filename, const int format);

		/**
		* @brief Generates a random map.
		**/
		void generate();

		/**
		* @brief Adds a TileLayer to the rendering list.
		* @param tileLayer The TileLayer to add.
		**/
		void addTileLayer(TileLayer tileLayer);

		/**
		* @brief Gets the TileLayers of this Map.
		* @returns The TileLayers of this Map.
		**/
		vector<TileLayer> getLayers();

		/**
		* @brief Gets a pointer to this Map's Viewport.
		* @return This Map's viewport.
		**/
		Viewport* getViewport();
		
	};

	typedef boost::shared_ptr<Map> pMap;

}// love

#endif