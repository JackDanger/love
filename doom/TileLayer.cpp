#include "TileLayer.h"
#include "Tileset.h"
#include "Tile.h"
#include "Map.h"
#include "Viewport.h"

#include <cmath>
#include <ctime>

namespace love 
{


	TileLayer::TileLayer()
	{
		setType(LOVE_TYPE_TILE_LAYER);
	}

	TileLayer::TileLayer(unsigned int width,unsigned int height, Tileset * tileset, Map* parent, 
						 float scrollWeight, float xOffset, float yOffset, bool xRepeat, bool yRepeat,
						 unsigned short* raw)
	{

		setType(LOVE_TYPE_TILE_LAYER);

		this->lastTileId = Tile::NULL_TILE;
		this->scrollWeight = scrollWeight;

		this->tileset		= tileset;
		this->parent		= parent;

		this->xOffset = xOffset;
		this->yOffset = yOffset;

		this->xRepeat = xRepeat;
		this->yRepeat = yRepeat;

		this->width			= width;
		this->height		= height;

		// Generate repeat data
		if(xRepeat)
		{



		}

		this->size = this->width * this->height;
		this->tiles = new Tile[this->size];
		this->list = glGenLists(size);

		// Load tiles if supplied
		if(raw != 0)
		{
			for(unsigned int i = 0; i<size;i++)
			{
				tiles[i].setId(raw[i]);
				tiles[i].setX((float)((i%width)*tileset->getTileWidth()));
				tiles[i].setY((float)((i/width)*tileset->getTileWidth()));

			}	
		}	
	}



	TileLayer::~TileLayer()
	{
	}

	void TileLayer::update(float dt)
	{

	}

	void TileLayer::render()
	{

		// Maybe later ...
		//glEnable(GL_POINT_SPRITE);
		//glDisable(GL_POINT_SPRITE);

		glPointSize(this->getTileset()->getTileWidth());

		glColor4ub(255,255,255,getOpacity());

		glPushMatrix();

			rect r				= getVisibleRect();
			array_section as	= getVisibleTiles();

			glTranslatef(getTranslationX(),getTranslationY(), 0.0);

			render(as);

		glPopMatrix();

		

		if(xRepeat){

		}


	}


	void TileLayer::render(array_section as)
	{

		// Loop through all tiles
		for(int i = 0; i< as.size;i++)
		{
			
			int vtx = (unsigned int)((i/as.width)*width);
			int vty = (unsigned int)(i % as.width);
			unsigned int id = as.start + vtx + vty;

			unsigned int tid = tiles[id].getId();

			if(tid == Tile::NULL_TILE)// Do not render 0 tiles
				continue;

			// Bind texture if id changes
			if(this->lastTileId != tid)
			{
				tileset->bindTile(tid);
				this->lastTileId = tid;
			}


			/**
			* Render as point sprites
			

			glPushMatrix();
				glTranslatef(tiles[id].getX(),tiles[id].getY(),0);
				glColor3ub(255,255,255);
					glBegin(GL_POINTS);
						glVertex2f(0,0);
					glEnd();
			glPopMatrix();
			**/

			/**
			** Render as quads
			**/

			/** 1st edition
			glPushMatrix();
				glTranslatef(tiles[id].getX(),tiles[id].getY(),0);
				glColor3ub(255,255,255);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0,1.0); glVertex2i(0,0);
					glTexCoord2f(0.0,0.0); glVertex2i(0, tileset->getTileHeight());
					glTexCoord2f(1.0,0.0); glVertex2i(tileset->getTileWidth(),tileset->getTileHeight());
					glTexCoord2f(1.0,1.0); glVertex2i(tileset->getTileWidth(),0);	
				glEnd();
			glPopMatrix();
			**/

			/**
			* 2nd edition
			**/
			
			glBegin(GL_QUADS);
				glTexCoord2f(0.0,0.0); glVertex2f(tiles[id].getX(),tiles[id].getY());
				glTexCoord2f(0.0,1.0); glVertex2f(tiles[id].getX(),tiles[id].getY()+ tileset->getTileHeight());
				glTexCoord2f(1.0,1.0); glVertex2f(tiles[id].getX()+tileset->getTileWidth(),tiles[id].getY()+ tileset->getTileHeight());
				glTexCoord2f(1.0,0.0); glVertex2f(tiles[id].getX()+tileset->getTileWidth(),tiles[id].getY());	
			glEnd();

			
			

		}
	}



	/**
	* Returns the rectangle in layer-coordinates (in pixels) that is
	* visible within the viewport. 
	**/
	rect TileLayer::getVisibleRect()
	{

		rect r;
		r.x = -getTranslationX();
		r.y = -getTranslationY();
		r.width = parent->getViewport()->getWidth();
		r.height = parent->getViewport()->getHeight();

		// Check that visible rect does not overstep it's bounds

		if(r.x <0)// Left
		{
			r.width += r.x;
			r.x = 0;
		}
		else if((r.x + r.width) > (width*tileset->getTileWidth()))// Right
		{
			r.width += (width*tileset->getTileWidth()) - (r.x + r.width);
		}

		if(r.y < 0)// Top
		{
			r.height += r.y;
			r.y = 0;
		}
		else if((r.y + r.height) > (height*tileset->getTileHeight()))// Bottom
		{
			r.height += (height*tileset->getTileHeight()) - (r.y + r.height);
		}
		
		// Check that size of visual area is not larger than the layer itself
		if(r.width > (width*tileset->getTileWidth()))
			r.width = (float)(width*tileset->getTileWidth());

		if(r.height > (height*tileset->getTileHeight()))
			r.height = (float)((height)*tileset->getTileHeight());

		return r;
	}

	bool TileLayer::isWithinViewport()
	{

		rect r = getVisibleRect();

		// Check on x axis
		if(-getTranslationX() > (width * tileset->getTileWidth()))
			return false;
		else if(-getTranslationX() < -parent->getViewport()->getWidth())
			return false;


		// Y axis
		if(-getTranslationY() > (height * tileset->getTileHeight()))
			return false;
		else if(-getTranslationY() < -parent->getViewport()->getHeight())
			return false;

		return true;
	}

	/**
	* Returns information about an rectangular section
	* of 
	**/ 
	array_section TileLayer::getVisibleTiles()
	{
		array_section as;

		if(!isWithinViewport())
		{
			as.width = 0;
			as.height = 0;
			as.size = 0;
			return as;
		}

		rect r = getVisibleRect();

		// Calculations look cleaner with these
		int tw = tileset->getTileWidth();
		int th = tileset->getTileHeight();

		// Get the first tile
		as.start	= ((int)(r.y/th))*width + ((int)(r.x/tw)) % width;

		// Get the width and height in tiles
		as.width	= (int)ceil(r.width/tw);
		as.height	= (int)ceil(r.height/th);

		// Calculate size
		as.size = as.width * as.height;

		return as;
	}


	float TileLayer::getTranslationX()
	{
		return -(parent->getViewport()->getX()*scrollWeight)+xOffset;
	}

	float TileLayer::getTranslationY()
	{
		return -(parent->getViewport()->getY()*scrollWeight)+yOffset;
	}

	void TileLayer::generate(array_section as, int xMul)
	{

			for(int i=0;i<as.size;i++)
			{
					int rand_id = rand()%tileset->getSize();

					while(rand_id == 0)
						rand_id = rand()%tileset->getSize();
					
						

					tiles[i].setId(rand_id);
					tiles[i].setX((float)((i%as.width)*tileset->getTileWidth()));
					tiles[i].setY((float)((i/as.width)*tileset->getTileWidth()));
			}

	}

	void TileLayer::generate()
	{
		array_section as;
		as.start = 0;
		as.width = width;
		as.height = height;
		as.size = as.width*as.height;

		generate(as, 1);
	}

	void TileLayer::setTileset(Tileset *tileset)
	{
		this->tileset = tileset;
	}

	Tileset* TileLayer::getTileset()
	{
		return this->tileset;
	}

	bool TileLayer::operator == (TileLayer &t)
	{
		return this->size == t.size;
	}

	bool TileLayer::operator < (TileLayer &t)
	{
		return this->size < t.size;
	}

	unsigned int TileLayer::getWidth()
	{
		return this->width;
	}

	unsigned int TileLayer::getHeight()
	{
		return this->height;
	}


} // love