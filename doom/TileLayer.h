/**
* @file TileLayer.h
* @author Anders Ruud
* @date 2006-02-07
* @brief Contains definition for class TileLayer, and 
* the struct array_selection.
**/

#ifndef AMF_TILELAYER_H
#define AMF_TILELAYER_H

#include "Layer.h"
#include <string>

#include "rect.h"

namespace love 
{

	// Forward declarations
	class Tileset;
	class Tile;
	class Map;

	

	/**
	* @struct array_section
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief This struct defines a section of an array.
	**/
	struct array_section
	{
		int start;
		int width; 
		int height;
		int size;
	};

	/**
	* @class TileLayer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Represents a logical layer consisting of tiles.
	* @see For other types of layers see sublclasses of Layer.
	**/
	class TileLayer : public Layer 
	{
	private:

		int lastTileId;

		// The Map this layer belongs to.
		Map* parent;

		// A pointer to the current tileset used.
		Tileset * tileset;

		// The size of the layer (in tiles)
		unsigned int width;
		unsigned int height;
		unsigned int size;

		unsigned int list;

		// How much the background should scroll relative to the camera
		float scrollWeight;

		// This holds our actual tile data
		Tile * tiles;


	public:
		
		/**
		* @brief Creates a new TileLayer object.
		**/ 
		TileLayer();

		/**
		* @brief Creates a new TileLayer object.
		* @param width The width of the layer in tiles.
		* @param height The height of the layer in tiles.
		* @param tileset A pointer to the Tileset this layer uses.
		* @param parent A pointer to the parent Map object.
		* @param scrollWeight How much this layer should scroll when the viewport 
		* is moved.
		* @param xOffset Optional left offset.
		* @param yOffset Optional top offset.
		* @param xRepeat Whether or not the layer should repeat on the x-axis. (Optional)
		* @param yRepeat Whether or not the layer should repeat on the y-axis. (Optional)
		* @param raw Raw tile data to create a layer from. (Optional)
		**/
		TileLayer(unsigned int width,unsigned int height, Tileset * tileset, Map* parent, 
			float scrollWeight,float xOffset = 0.0f, float yOffset = 0.0f,  bool xRepeat = false, 
			bool yRepeat = false,  unsigned short* raw = 0);

		virtual ~TileLayer();

		/**
		* @brief Returns the width in tiles.
		* @return The width in tiles.
		**/
		unsigned int getWidth();

		/**
		* @brief Returns the height in tiles.
		* @return The height in tiles.
		**/
		unsigned int getHeight();


		/**
		* @brief Whether or not the layer is visible given the current Viewport.
		* @param True if some part of the layer is visible, false otherwise.
		* 
		**/ 
		bool isWithinViewport();

		/**
		* @brief Gets the current visible area.
		* @return A rect that represents the current visible area.
		*
		* The visible area means the area of the layer that is
		* rendered to the screen. The values are on pixels, not in tiles, 
		* and they are layer-relative. <br />
		* One might think that this is easily computed from the parent Map's 
		* Viewport, but due to different offsets and scrolling speeds, 
		* a dedicated function is needed.
		**/
		rect getVisibleRect();

		/**
		* @brief Returns the current tiles that are visible on screen.
		* @return An array_section representing the portion of the array
		* the needs to be rendered.
		* @see Based on results from getVisibleRect()
		**/
		array_section getVisibleTiles();

		/**
		* @brief Changes the current Tileset.
		* @param tileset The new tileset.
		*
		* This can be useful when you quickly need to change the the graphics
		* on a layer.
		**/
		void setTileset(Tileset * tileset);

		/**
		* @brief Returns a pointer to the current Tileset.
		* @return A pointer to the current Tileset.
		**/
		Tileset* getTileset();

		/**
		* @brief Returns the translation needed to move it according
		* to the viewport.
		* @return The translation distance needed on the x-axis.
		**/
		float getTranslationX();

		/**
		* @brief Returns the translation needed to move it according
		* to the viewport.
		* @return The translation distance needed on the y-axis.
		**/
		float getTranslationY();

		/**
		* @brief Renders the layer once.
		**/
		void render();

		/**
		* @brief Renders the specified tiles.
		* @param as The section of the tile array that
		* we want to render.
		**/
		void render(array_section as);

		/**
		* @brief Updates the layer.
		* @param dt Time (seconds) since last frame.
		**/
		void update(float dt);

		/**
		* @brief Generates random tiles.
		**/
		void generate();

		/**
		* @brief I have completely forgotten what this method does, 
		* and why it's here.
		**/
		void generate(array_section as, int xMul);

		/**
		* @brief Compares two TileLayers.
		* @param t The TileLayer we want to compare this with.
		* @return True if the number of tiles is equal, false otherwise.
		**/
		bool operator == (TileLayer &t);

		/**
		* @brief Compares two TileLayers.
		* @param t The TileLayer we want to compare this with.
		* @return True if the number of tiles is less t's number 
		* of tiles, false otherwise.
		**/
		bool operator < (TileLayer &t);


	};

	typedef boost::shared_ptr<TileLayer> pTileLayer;

}// love


#endif