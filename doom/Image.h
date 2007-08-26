/**
* @file Image.h
* @brief Contains definition of class Image.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef LOVE_IMAGE_H
#define LOVE_IMAGE_H


// LOVE
#include "Sprite.h"
#include "Color.h"
#include "Loadable.h"

// STL
#include <string>

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
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-09-03
	* @brief Alpha, Luminance
	**/
	struct la
	{
		unsigned char l;
		unsigned char a;
	};

	/**
	* @struct rgb
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
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
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
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
	* @class Image
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief An image wrapper using DevIL.
	*
	* Also contains some methods for image manipulation. <br />
	* This class can load almost any image format (any format DevIL is capable of). <br />
	* For more information about DevIL see http://openil.sourceforge.net/ 
	**/
	class Image : public Sprite
	{
	public:

		/**
		* LOCK means that the Image is passed to OpenGL. After that the pixels
		* can no longer be manipulated. <br />
		* TWO_POWER means that the Image is automatically converted into a power-of-two Image. 
		* (For OpenGL < 2.0 compatibility).<br />
		* LOAD is for loading an Image from a file as the Image object is beeing created. (As opposed
		* to loading it later, via load()).<br />
		* @see load()
		**/
		static enum OPTIONS
		{
			LOCK		= 0x0001,
			TWO_POWER	= 0x0002, 
			LOAD		= 0x0004
		};

	private:

		float rotation;

		// Path to file
		string filename;

		// GL storage
		unsigned int glTexture;

		// IL image pointer
		ILuint image;

		// Holds the actual pixels
		unsigned char * data;
		
		// tga, png, bmp etc (One of the above constants)
		unsigned char fileType;

		// What order the colors are in, etc (RBG, BGR, RGBA etc)
		GLenum dataFormat;
			
		// How many bytes for one pixel. (WARNING: BYTES, not bits)
		unsigned char colorDepth;

		// Dimensions of the Image.
		unsigned short width;
		unsigned short height;

		// The product of width, height and colorDepth.
		unsigned int size;

		// If (0,0) means top left of top right.
		unsigned int origin;


		/**
		* @brief Convert to the closest high-value power-of-two number.
		* @return The closest high-value power-of-two number.
		**/
		int toTwoPower(int num);

		/**
		* @brief Gets the number of bytes for each pixel based on the Image type.
		* @param glType The Image type.
		* @return The number of bytes for the Image type.
		**/
		static int toBytesPerPixel(int glType);


	public:

		/**
		* @brief Creates a new, empty Image object.
		**/
		Image();

		/**
		* @brief Allocates memory for an empty Image.
		* @param width The width of the Image.
		* @param height The height of the Image.
		* @param glType The Image type.
		* @todo: MUST USE DEFAULT GLTYPE AFAIK! MAKE ROBUST!
		**/
		Image(int width, int height, int glType = GL_RGBA);

		/**
		* @brief Creates a new Image.
		* @param width The width of the Image.
		* @param height The height of the Image.
		* @param data The data representing the Image.
		* @param glType The Image type.
		* @param options Can be LOCK or TWO_POWER.
		* @see OPTIONS
		**/
		Image(int width, int height, unsigned char * data, int glType = GL_RGBA, int options = 0);

		/**
		* @brief Creates a new Image from a file.
		* @param filename The filename of the file to load the Image from.
		* @param options Can be LOCK, TWO_POWER, LOAD
		* @warning This does not actually load the Image data.
		* @see OPTIONS
		* @see load()
		**/
		Image(const string & filename, int options = 0);

		// Destructor
		virtual ~Image();

		/**
		* @brief Loads the Image if a filename is detected.
		* @return True if the Image loaded, false otherwise.
		**/
		void load();

		void unload();

		/**
		* @brief Removes all pixels of a certain Color.
		* @param c The color to remove.
		* RGBA Images only! It sets the alpha of all the relevant 
		* pixels to 0.
		**/
		void stripColor(const Color & c);

		/**
		* @brief Fills Image with one color.
		**/
		void fill(const Color & c);

		/**
		* @brief Pastes Image on this Image. (Copies pixels).
		* @param image The Image wanted pasted onto this.
		* @param dx Destination x-coordinate on this Image.
		* @param dy Destination y-coordinate on this Image.
		* @param sx Source x-coordinate on source Image.
		* @param sy Source y-coordinate on source Image.
		* @param sw Source width on source Image.
		* @param sh Source height on source Image.
		*
		* If you want to paste the entire source Image, just pass dx and dy.
		* It is also possible paste a subtexture of the source Image. 
		* In this case, use sx, sy, sw and sh as well.
		**/
		void paste(const Image & image, int dx, int dy, int sx = -1, int sy = -1, int sw = -1, int sh = -1);

		/**
		* @brief Converts a Image's dimensions to be power of 2.
		* This is useful for target hardware where OGL version < 2.0.
		**/
		void twoPower();

		/**
		* @brief Passes the Image data to the GPU
		**/
		void lock();

		/**
		* @brief Binds the Image.
		**/
		void bind();

		/**
		* @brief Renders the Image at (0,0).
		**/
		void render();

		/**
		* @brief Renders the image at a certain position.
		**/
		void render(float x, float y);

		/**
		* @brief Renders the defined rectangle at (0,0);
		* If the rectangle is outside the texture area, nothing is rendered.
		**/
		void render(float x, float y, float width, float height);

		void sendTextureCoordinates(float x, float y, float width, float height);

		/**
		* @brief Renders the defined rectangle at a certain point
		* If the rectangle is outside the texture area, nothing is rendered.
		**/
		void render(float x, float y, float rx, float ry, float width, float height);

		/**
		* @brief Flips the image vertically.
		* @return True if it succeeded, false otherwise.
		**/
		bool flipVertical();

		//TODO: bool flipHorizontal();

		/**
		* @brief Sets the alpha in this Image.
		* @param alpha The new alpha value. (0-255)
		* @return True if alpha change succeeded, false
		* otherwise.
		**/ 
		bool setAlpha(const unsigned char alpha);

		/**
		* @brief Swaps red and blue colors.
		**/
		void swapRedBlue();

		/**
		* @brief Gets the raw image data for OpenGL
		* texture use.
		* @return Texture data as an array of chars.
		**/
		unsigned char * getPixels() const;

		/**
		* @brief Gets the raw sub-image data for OpenGL
		* texture use.
		* @return Texture data as an array of chars.
		* @param x The left indent of the sub image.
		* @param y The right indent of the sub image.
		* @param width The width of the sub image.
		* @param height The height of the sub image.
		**/
		unsigned char * getPixels(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const;

		
		/**
		* @brief Gets the width of the image in pixels.
		* @return The width of the image.
		**/
		unsigned short getWidth() const;

		/**
		* @brief Gets the height of the image in pixels.
		* @return The height of the image.
		**/
		unsigned short getHeight() const;

		/**
		* @brief Gets the format of the image data.
		* @return The format of the image data, represented
		* by one of the OpenGL constants. (GL_RGBA, GL_RGB, etc)
		*
		* For more information about diffrent image type constants,
		* see OpenGL documentation, or OGL header file.
		**/
		GLenum getFormat() const;

		/**
		* @brief Gets the number of bytes per pixel.
		* @return Number of bytes per pixel.
		*
		* The return value will typically be 4 for
		* images with color and alpha channel.
		**/
		unsigned char getBytesPerPixel() const;

		/**
		* @brief Used to determine if the origin is
		* top left or bottom left.
		* @return Origin constant.
		* 
		* For more information see DevIL header file.
		**/
		unsigned int getOrigin() const;

		/**
		* @brief Gets filename.
		* @return filename.
		**/
		const string & getFilename() const;

		/**
		* @brief Gets the number of bytes. 
		* @return The number of bytes.
		**/
		int getSize() const;

		/** TO DO NOW **/
		void setRotation(float rotation);
		float getRotation() const;

	};

	typedef boost::shared_ptr<Image> pImage;

} // love

#endif
