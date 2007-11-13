/**
* @file AbstractImage.h
* @author Anders Ruud
* @date 2007-01-27
* @brief Contains definition for class AbstractImage.
**/

#ifndef LOVE_ABSTRACTIMAGE_H
#define LOVE_ABSTRACTIMAGE_H

// LOVE
#include "Sprite.h"
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

// DevIL
#include <IL/ilut.h>
#include <string>

// Using
using std::string;

namespace love
{
	/**
	* @struct la
	* @brief Alpha, Luminance
	**/
	struct la
	{
		unsigned char l;
		unsigned char a;
	};

	/**
	* @struct rgb
	* @brief Represents the primary
	* colors of a pixel.
	**/
	struct rgb
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};

	/**
	* @struct rgb
	* @brief Represents the primary
	* colors and opacity of a pixel.
	**/
	struct rgba
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	/**
	* @class AbstractImage
	* @brief 
	**/
	class AbstractImage : public Sprite
	{
	private:

		bool extlibinit;

	protected:

		// image
		ILuint image;

		// texture
		GLuint texture;

		void initExternalLibraries();

		float actualWidth;
		float actualHeight;

	public:

		/**
		* @brief Contructs an empty AbstractImage.
		**/
		AbstractImage();
		virtual ~AbstractImage();

		/**
		* @brief Gets image.
		* @return image.
		**/
		const ILuint getImage() const;

		/**
		* @brief Gets texture.
		* @return texture.
		**/
		const GLuint getTexture() const;
	
		virtual int load();
			
		/**
		* @brief Deletes DevIL image and OpenGL image.
		**/
		virtual void unload();

		virtual void bind();
		virtual void beginRender();
		virtual void sendVertices();
		virtual void sendVertices(float x, float y, float width, float height);
		virtual void endRender();

		virtual renderinfo getRenderInfo();
		virtual renderinfo getRenderInfo(float x, float y, float width, float height);
		

		void render();

		void render(float x, float y);

		void render(float x, float y, float width, float height);

		/**
		* @brief Renders sprite onto the the quad given by the vertices.
		* Vertices must be in counter clockwise order.
		*
		* @param x1 X-coordinate of first point.
		* @param y1 Y-coordinate of first point.
		* @param x2 X-coordinate of second point.
		* @param y2 Y-coordinate of second point.
		* @param x3 X-coordinate of third point.
		* @param y3 Y-coordinate of third point.
		* @param x4 X-coordinate of fourth point.
		* @param y4 Y-coordinate of fourth point.
		**/
		void renderQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


	};

	typedef boost::shared_ptr<AbstractImage> pAbstractImage;

} // love

#endif

