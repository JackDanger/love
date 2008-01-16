/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_IMAGE_H
#define LOVE_IMAGE_H

// LOVE
#include "Sprite.h"
#include "Resource.h"

namespace love
{

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
		//friend class Animation;

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

		// From Sprite.
		// Overriding this here. Images are not supposed to 
		// change over time.
		void update(float dt);

		/**
		* Render the Image as a quad specified by the parameters.
		* @param vertices The vertices of the quad.
		* @param texels The texture coordinates of each vertex.
		**/
		//virtual void render(vec2f * vertices, vec2f * texels) const = 0;

	};

	typedef boost::shared_ptr<Image> pImage;

	// Pixel format structures. Luminance-Alpha and RGB(A).
	// These might be useful to subclasses that need to convert images
	// to power-of-two textures, and need to work with pixel data in general.
	struct la { unsigned char l, a; };
	struct rgb { unsigned char r, g, b; };
	struct rgba { unsigned char r, g, b, a; };

} // love

#endif // LOVE_IMAGE_H
