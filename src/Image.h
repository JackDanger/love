/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_IMAGE_H
#define LOVE_IMAGE_H

// LOVE
#include "Sprite.h"
#include "Resource.h"

namespace love
{

	// Pixel format structures. Luminance-Alpha and RGB(A).
	// These might be useful to subclasses that need to convert images
	// to power-of-two textures, and need to work with pixel data in general.
	struct la { unsigned char l, a; };
	struct rgb { unsigned char r, g, b; };
	struct rgba { unsigned char r, g, b, a; };

	/**
	* An Image is a Sprite that is always
	* rendered the same way on the screen.
	* 
	* @author Anders Ruud
	* @date 2007-05-18
	**/
	class Image : public Sprite, public Resource
	{
		// Friend classes.
		friend class Animation;

	protected:

		// The size of the actual texture in hardware
		// memory. This may be different to normal width/height 
		// due to power-of-two conversion. 
		float textureWidth;
		float textureHeight;

		// If an Image should linger in memory after load has been
		// called. Normally, this is set to false, meaning that
		// the Image will only be available as a hardware texture
		// after load has been called.
		bool linger;

		// The image's padding.
		int padding;

		int origin;

	public:

		/**
		* Constructs an empty Image. textureWidth and
		* textureHeight are both set to 0.
		**/
		Image(pFile file);

		/**
		* Constructs an empty Image with the option to not immediately
		* unload the Image data from memory. This is useful when other
		* classes need access to the pixel data.
		* @param linger True if the image should linger in memory, 
		* false otherwise.
		**/
		Image(pFile file, bool linger);

		virtual ~Image();

		// Note: load() (in subclasses) should just contain 
		// these method calls:
		// readData()
		// toHardware()
		// freeData()

		/**
		* Read the data from the file.
		**/
		virtual bool readData() = 0;

		/**
		* Gets a pointer to the pixel data. The size
		* can be retrieved using getWidth/getHeight.
		**/
		virtual rgba * getData() const = 0;

		/**
		* Converts the image data to a hardware texture.
		* Also performs power-of-two conversions if needed.
		**/
		virtual bool toHardware() = 0;

		/**
		* Frees the "local" image data.
		**/
		virtual void freeData() = 0;

		// From Sprite.
		// Overriding this here. Images are not supposed to 
		// change over time.
		void update(float dt);

		/**
		* Render the Image as a quad specified by the parameters.
		* @param vertices The vertices of the quad. (Array size of 8 is assumed).
		* @param texels The texture coordinates of each vertex. (Array size of 8 is assumed).
		* @param x The position on the x-axis.
		* @param y The position on the y-axis.
		* @param angle The angle of rotation.
		* @param sx Scale factor along the x-axis.
		* @param sy Scale factor along the y-axis.
		**/
		virtual void render(const float * vertices, const float * texels, float x, float y, 
			float angle, float sx, float sy, float cx, float cy) const = 0;

		// From Sprite.
		virtual void render() const = 0;
		virtual void render(float x, float y) const = 0;
		virtual void render(float x, float y, float width, float height) const = 0;
		virtual void render(float x, float y, float angle, float sx, float sy) const = 0;

		/**
		* Extends color data one pixel into the area where alpha = 0.
		* This makes images artifact-free when rotated, stretched, etc.
		**/
		virtual void optimizeAlpha() = 0;

		/**
		* Pads the image with a border of transparent
		* pixels.
		**/
		virtual void pad(int size = 1) = 0;

	};

	typedef boost::shared_ptr<Image> pImage;

} // love

#endif // LOVE_IMAGE_H
