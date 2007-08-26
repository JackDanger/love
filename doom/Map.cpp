#include "Map.h"
#include "TileLayer.h"
#include "Tileset.h"
#include "Viewport.h"
#include "Base64.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include "xmlParser.h"

namespace love
{

	Map::Map()
	{
		srand((unsigned int)time(0));
		viewport = new Viewport(0,0,2000000*32,2000000*32, 1024,800);
		setType(LOVE_TYPE_MAP);
	}

	Map::~Map()
	{	
		delete viewport;
	}

	void Map::restrainViewport()
	{

		float xMax = 0;
		float yMax = 0;

		float xMin = 0;
		float yMin = 0;

		for each(TileLayer l in tileLayers)
		{
			float width = (float)(l.getTileset()->getTileWidth()*l.getWidth());
			float height = (float)(l.getTileset()->getTileHeight()*l.getHeight());

			float x = l.getOffsetX();
			float y = l.getOffsetY();

			if(x < xMin)
				xMin = x;
			if(y < yMin)
				yMin = y;

			if(width > xMax)
				xMax = width;
			if(height > yMax)
				yMax = height;

		}

		viewport->setConstraints(xMin, xMax - viewport->getWidth(), yMin, yMax - viewport->getHeight());
	}

	void Map::update(float dt)
	{
		viewport->update(dt);
	}

	/**
	* This method renders everything on the map.
	**/
	void Map::render()
	{

		glLoadIdentity();

		glEnable(GL_TEXTURE_2D);

		// Loops through every tilelayer and renders it.
		for each(TileLayer l in tileLayers)
		{
			//l->generate(); // Only do this if you want to generate a new map each frame
			l.render();
		}

		glDisable(GL_TEXTURE_2D);
	}

	/**
	* Generates a random map.
	**/
	void Map::generate()
	{

		// Only do this first time
		if(this->tileLayers.size() == 0)
		{
			float dist = 50.0f;

			for(int i =0;i<3;i++)
				addTileLayer(TileLayer(200,200,new Tileset("data/map32.tga",32,32),this, (i*0.3f)+1.0f, dist*i, dist*i));
			//addTileLayer(new TileLayer(200,200,new Tileset("map32.tga",32,32),this,1.0f));

			// REPEAT BETA PLZ!!1
			//addTileLayer(new TileLayer(10,10,new Tileset("map.tga",16,16),this,1.0f, 0.0f, 0.0f, true));

			addTileLayer(TileLayer(100,100,new Tileset("data/map.tga",16,16),this,2.0f, 200.0f, 200.0f));
			addTileLayer(TileLayer(10,10,new Tileset("data/map.tga",16,16),this,2.0f, 20.0f, 20.0f));

			//addTileLayer(new TileLayer(10,10,new Tileset("map.tga",32,32),this, 1.0f, 2000.0f, 2000.0f));

			/**
			int lh = 4;

			for(int i=0;i<5;i++)
			{
				addTileLayer(new TileLayer(60+(i*lh),48-(i*lh),new Tileset("map32.tga", 32, 32), this, (float)i, 0.0f, (float)(i*lh*32)));	
			}

			addTileLayer(new TileLayer(10,10,new Tileset("map.tga",16,16),this,0.0f, 200.0f, 200.0f));
			addTileLayer(new TileLayer(20,20,new Tileset("map.tga",16,16),this,5.0f, 400.0f, 300.0f));
			**/
		}

		// Generate random layers
		for each(TileLayer l in tileLayers)
			l.generate();

	}

	/**
	* Adds a TileLayer to the Map.
	**/
	void Map::addTileLayer(TileLayer tileLayer)
	{
		tileLayers.push_back(tileLayer);
	}

	/**
	* This method is supposed to detect the filetype, 
	* and then call load(filename, format)
	**/
	bool Map::load(string filename)
	{
		return false;
	}

	/**
	* Reads a map file from the filename with the given format.
	**/
	bool Map::load(string filename, const int format)
	{

		// Open a file pointer
		FILE * file;
		fopen_s(&file, filename.c_str(), "rb");
		
		// Check that file exists
		if(!file)
		{
			printf("Map: File not found.");
			return false;
		}



		// Holds our raw tile data bytes
		unsigned short* raw;


		if(format == FORMAT_TILED)
		{
			
			XMLNode xNode;
			XMLNode xData;

			// Open Main node
			XMLNode xMainNode = XMLNode::openFileHelper(filename.c_str(),"map");

			// Get map size
			int width	= atoi(xMainNode.getAttribute("width"));
			int height	= atoi(xMainNode.getAttribute("height"));
			int tiles	= width*height;

			// Get tileset (Only get the first one, and apply to all layers);
			xNode = xMainNode.getChildNode("tileset");
			int tileWidth	= atoi(xNode.getAttribute("tilewidth"));
			int tileHeight	= atoi(xNode.getAttribute("tileheight"));
			int refid		= atoi(xNode.getAttribute("firstgid"));

			string tileset	= "./data/";
			tileset.append(xNode.getChildNode("image").getAttribute("source"));
			


			// Get all layers
			int numLayers = xMainNode.nChildNode("layer");

			// Get data for all layers
			int iterator = 0;

			for(int i=0;i<numLayers;i++)
			{
		
				// Get the current layer.
				xNode = xMainNode.getChildNode("layer", &iterator);
				xData = xNode.getChildNode("data");

				// Get opacity

				string opacity_string;
				float opacity;

				if(xNode.isAttributeSet("opacity"))
				{
					opacity_string = xNode.getAttribute("opacity");
					opacity = (float)atof(opacity_string.c_str());
				}else
					opacity = 1.0f;

				// Get the current raw data
				string data = Base64::decode(xData.getText());

				// Allocate memory for the tiles.
				raw = new unsigned short[tiles];

				// Convert all the tiles into something we can use. (Max 256 different tiles as of currently)
				for(int i=0;i<tiles;i++)
					raw[i] = (unsigned char)data.at(i*4)-refid;

				// Add the layer
				addTileLayer(TileLayer(width,width,new Tileset(tileset,tileWidth,tileHeight),this,1.0f, 0.0f, 0.0f, false, false, raw));

				// Set opacity
				this->tileLayers.back().setOpacity((unsigned char)(opacity*255));

			}
			

		}else
		{
			MessageBoxA(0, "Unsupported file format.", "Error.", MB_OK);
			return false;
		}


		fclose(file);

		restrainViewport();

		return true;
	}

	Viewport* Map::getViewport()
	{
		return this->viewport;
	}

	vector<TileLayer> Map::getLayers()
	{
		return this->tileLayers;
	}

}// love