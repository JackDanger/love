#include "Image.h"

#include <cmath>
#include <fstream>

namespace love 
{


	Image::Image()
	{
		rotation = 0;

		setType(LOVE_TYPE_IMAGE);
	}

	Image::Image(int width, int height, int glType) :  glTexture(-1), width(width), height(height), dataFormat(glType), filename("")
	{
		rotation = 0;

		colorDepth = toBytesPerPixel(glType);

		// Size of image in bytes
		size = width * height * colorDepth;

		// Allocate memory
		data = new unsigned char[size];

		// Clear background
		fill(Color(0,0,0,0));
	}

	Image::Image(int width, int height, unsigned char * data, int glType, int options) : glTexture(-1), width(width), height(height), dataFormat(glType), filename("")
	{
		rotation = 0;

		colorDepth = toBytesPerPixel(glType);

		// Size of image in bytes
		size = width * height * colorDepth;

		// Allocate memory
		this->data = new unsigned char[size];

		// Copy memory
		memcpy(this->data, data, size);

		// Convert to twoPower?
		if((options & TWO_POWER) != 0)
			twoPower();

		// Load pixels?
		//if((options & LOAD) != 0)
		//	Warning: cannot load images that are not from files.

		// Create image
		if((options & LOCK) != 0)
			lock();
	}

	Image::Image(const string & filename, int options) : glTexture(-1), filename(filename)
	{
		rotation = 0;

		// Init DevIL
		ilInit();

		data = 0;

		// Generate a DevIL image
		ilGenImages(1,&image);

		// Set load description
		setLoadDescription("Loading: " + filename);

		// Load pixels?
		if((options & LOAD) != 0)
			load();

		// Convert to twoPower?
		if((options & LOAD) && (options & TWO_POWER))
			twoPower();

		// Create image
		if((options & LOAD) && (options & LOCK))
			lock();
	}

	Image::~Image()
	{
		// Cleanup
		ilDeleteImages(1, &image);
	}

	void Image::stripColor(const Color & c)
	{
		if(dataFormat != GL_RGBA)
			return;

		rgba* pixels = (rgba*)data;

		int pxsize = width*height;

		for(int i=0;i<pxsize;i++)
		{
			if(c.getRed() == pixels[i].r && c.getGreen() == pixels[i].g && c.getBlue() == pixels[i].b)
				pixels[i].a = 0;
		}

	}

	int Image::toBytesPerPixel(int glType)
	{
		if(glType == GL_ALPHA || glType == GL_LUMINANCE )
			return 1;
		if(glType == GL_LUMINANCE_ALPHA)
			return 2;
		if(glType == GL_RGB)
			return 3;
		if(glType == GL_RGBA)
			return 4;

		return -1;

	}

	void Image::fill(const Color & c)
	{
		for(unsigned int i = 0; i < size; i+=colorDepth)
		{
			data[i]		= c.getRed();
			data[i+1]	= c.getGreen();
			data[i+2]	= c.getBlue();
			data[i+3]	= c.getAlpha();
		}
			
	}


	void Image::paste(const Image & image, int dx, int dy, int sx, int sy, int sw, int sh)
	{

		// Check formats
		if(dataFormat != image.getFormat())
			return;

		/**
		* @todo: Add some kind of error message in these cases.
		**/
		if(dx < 0 || dx > width || dy < 0 || dy > height)
			return; 

		// If source stuff is not specified ...
		if(sx == -1 || sy == -1 || sw == -1 || sh == 1)
		{
			// Then use entire source image.
			sx = 0;
			sy = 0;
			sw = image.getWidth();
			sh = image.getHeight();
		}else
		{
			// Checking ranges.

			if(sx < 0 || sx > image.getWidth() || sy < 0 || sy > image.getHeight())
				return; 	

			if(dx + sw > width)
				return;

			if(dy + sh > height)
				return;
		}

		// Casting current data into rgba for convenience
		rgba * rgbaDest = (rgba*)(data);
		rgb * rgbDest = (rgb*)(data);
		la * laDest = (la*)(data);

		// Source data
		const rgba * rgbaSource = (const rgba*)(image.getPixels());
		const rgb * rgbSource = (const rgb*)(image.getPixels());
		const la * laSource = (const la*)(image.getPixels());

		for(int i=0;i<sh;i++)
		{
			for(int j=0;j<sw;j++)
			{
				// Destination vars
				int destx = dx + j;
				int desty = dy + i;
				int desti = desty * width + destx;

				// Source vars
				int sourcex = sx + j;
				int sourcey = sy + i;
				int sourcei = sourcey * image.getWidth() + sourcex;

				// Change pixel at destination (unless completely transparent).

				if(colorDepth == 4)
				{
					rgbaDest[desti].r = rgbaSource[sourcei].r;
					rgbaDest[desti].g = rgbaSource[sourcei].g;
					rgbaDest[desti].b = rgbaSource[sourcei].b;
					rgbaDest[desti].a = rgbaSource[sourcei].a;

				}else if(colorDepth == 3)
				{
					rgbDest[desti].r = rgbSource[sourcei].r;
					rgbDest[desti].g = rgbSource[sourcei].g;
					rgbDest[desti].b = rgbSource[sourcei].b;	

				}else if(colorDepth == 2)	
				{
					laDest[desti].l = laSource[sourcei].l;
					laDest[desti].a = laSource[sourcei].a;

				}else if(colorDepth == 1)
				{
					data[desti] = image.getPixels()[sourcei];
				}

			}
		}
	}

	int Image::toTwoPower(int num)
	{
		int temp = 1;
		while(temp < num)
			temp *= 2;
		return temp;
	}

	void Image::twoPower()
	{

		// Find the twopower version of this image
		int nw = toTwoPower(width);
		int nh = toTwoPower(height);

		// Create a new image.
		Image t(nw, nh);
		t.fill(Color(0,0,0,0));
		
		// Paste this image onto the new one
		t.paste(*this, 0, 0);

		// Delete current image data
		//delete[] data;
		//@todo MAJOR MEMORY LEAK!!!!11111 Caused problems, so had to disable.
		data = 0;

		// Create new data
		data	= new unsigned char[t.getSize()];
		width	= nw;
		height	= nh;
		size	= t.getSize();
		
		// Copy image data from new image over to this one.
		memcpy(data, t.getPixels(), t.getSize());
		
	}

	void Image::lock()
	{

		// Generate image object
		glGenTextures(1,&glTexture);

		if(glTexture == 0)
			throw std::runtime_error("Fatal error at love::image. image object could not be created.");

		//@todo Use Core::error instead.

		// Bind the image
		glBindTexture(GL_TEXTURE_2D, glTexture);

		// How to resize the image.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Pass data to GL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

	}


	void Image::bind()
	{
		if(glTexture != -1)
			glBindTexture(GL_TEXTURE_2D,glTexture); 
	}

	void Image::load()
	{

		// Bind the image
		// All IL-functions will now apply to this image
		ilBindImage(image);

		//Load image
		ILboolean success = ilLoadImage((ILstring)filename.c_str());

		if(!success)
			return;

		// Convert data
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		// Get size etc
		width			= ilGetInteger(IL_IMAGE_WIDTH);
		height			= ilGetInteger(IL_IMAGE_HEIGHT);
		colorDepth		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		size			= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
		dataFormat		= ilGetInteger(IL_IMAGE_FORMAT);
		origin			= ilGetInteger(IL_IMAGE_ORIGIN);


		// Get data
		data = ilGetData();

	}

	void Image::unload()
	{

	}

	/**
	* Sets the alpha value for this image
	**/
	bool Image::setAlpha(const unsigned char alpha)
	{
		
		if(size <= 0)
			return false;

		rgba* source	= (rgba*)data;

		for(int i=0;i<(width * height);i++)
			source[i].a = 100;

		return true;

	}

	unsigned char * Image::getPixels() const
	{
		return data;
	}

	unsigned char * Image::getPixels(UINT x, UINT y, UINT width, UINT height) const
	{


		if(width*height <= 0)
		{
			width = 1;
			height = 1;
		}

		//size for the new data
		rgba* temp = new rgba[width*height];
		rgba* source	= (rgba*)data;

		//check that rectangle is inside the image
		if(x < 0 || x+width > this->width || y < 0 || y+height > this->height)
		{
			printf("getSubImage: invalid range");
			return NULL;
		}


		//Retrieve the new image data
		for(unsigned int i = 0; i < height ; i++)
		{
			for(unsigned int j = 0 ; j< width ;j++)
			{

				unsigned int ti = (i*width)+j;									// Temp index

				
				unsigned int si;		// Source index

				if(origin == IL_ORIGIN_LOWER_LEFT)// tga ...
					si = ((this->height-(y+i+1))*this->width) + (x+j);
				else if(origin == IL_ORIGIN_UPPER_LEFT)// png ...
					si = ((y+i)*this->width) + (x+j);	
				else
					si = ((y+i)*this->width) + (x+j);


				temp[ti].r = source[si].r;
				temp[ti].g = source[si].g;
				temp[ti].b = source[si].b;
				temp[ti].a = source[si].a;

			}
		}

		//f.close();

		return (unsigned char*)temp;
	}

	void Image::swapRedBlue()
	{
		unsigned char temp;
		rgba* source = (rgba*)data;

		for (int pixel = 0; pixel < (width * height); ++pixel)
		{
			temp = source[pixel].b;
			source[pixel].b = source[pixel].r;
			source[pixel].r = temp;
		}
	}

	bool Image::flipVertical()
	{
			rgba* tmpBits = new rgba[width];
			if (!tmpBits)
				return false;

			int lineWidth = width * 4;

			rgba* top = (rgba*)data;
			rgba* bottom = (rgba*)(data + lineWidth*(height-1));

			for (int i = 0; i < (height / 2); ++i)
			{
				memcpy(tmpBits, top, lineWidth); 
				memcpy(top, bottom, lineWidth);
				memcpy(bottom, tmpBits, lineWidth);

				top = (rgba*)((unsigned char*)top + lineWidth);
				bottom = (rgba* )((unsigned char*)bottom - lineWidth);
			}

			delete [] tmpBits;
			tmpBits = 0;

			return true;
	}

	void Image::render()
	{


		bind();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2i(0,0);
			glTexCoord2f(0.0,1.0); glVertex2i(0,height);
			glTexCoord2f(1.0,1.0); glVertex2i(width,height);
			glTexCoord2f(1.0,0.0); glVertex2i(width,0);
		glEnd();

		// Also render border
		/**
		glPushAttrib(GL_CURRENT_BIT);

			glDisable(GL_TEXTURE_2D);
			glColor4ub(0,255,0,150);
			glBegin(GL_LINE_LOOP);
				glVertex2i(0,0);
				glVertex2i(0,height);
				glVertex2i(width,height);
				glVertex2i(width,0);
			glEnd();
			glEnable(GL_TEXTURE_2D);

		glPopAttrib();
		**/

	}

	void Image::render(float x, float y)
	{
		glTranslatef(x, y, 0);

		glPushMatrix();
		glRotatef(rotation, 0, 0, 1);
		render();
		glPopMatrix();

		glTranslatef(-x, -y, 0);
	}




	void Image::render(float x, float y, float width, float height)
	{
		bind();

		sendTextureCoordinates(x, y, width, height);

	}

	void Image::sendTextureCoordinates(float x, float y, float width, float height)
	{
		float xTex = x/(float)this->width;
		float yTex = y/(float)this->height;

		float wTex = width/(float)this->width;
		float hTex = height/(float)this->height;


		glBegin(GL_QUADS);
			glTexCoord2f(xTex,yTex);				glVertex2i(0,0);
			glTexCoord2f(xTex,yTex+hTex);			glVertex2i(0,(int)height);
			glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2i((int)width,(int)height);
			glTexCoord2f(xTex+wTex,yTex);			glVertex2i((int)width,0);
		glEnd();		
	}

	void Image::render(float x, float y, float rx, float ry, float width, float height)
	{
		glTranslatef(floor(x), floor(y), 0);
		render(rx, ry, width, height);
		glTranslatef(-floor(x), -floor(y), 0);
	}

	unsigned char Image::getBytesPerPixel()  const
	{
		return this->colorDepth;
	}

	unsigned int Image::getOrigin()  const
	{
		return this->origin;
	}

	unsigned short Image::getWidth()  const
	{
		return this->width;
	}

	unsigned short Image::getHeight()  const
	{
		return this->height;
	}

	GLenum Image::getFormat()  const
	{
		return this->dataFormat;
	}

	const string & Image::getFilename() const
	{
		return filename;
	}

	int Image::getSize() const
	{
		return size;
	}

	void Image::setRotation(float rotation)
	{
		this->rotation = rotation;
	}

	float Image::getRotation() const
	{
		return rotation;
	}

}
