/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-31
**/

#include "Texture.h"

// STD
#include <iostream>

// DevIL
#include <IL/il.h>

// OpenGL
#include <SDL/SDL_opengl.h>

namespace love
{
namespace opengl
{
	// @todo why is this method even here?
	int power_of_two(int i)
	{
		// @todo Less "while", more awesome.
		// float exp = log(value) / log(2) // etc
		int temp = 1;
		while(temp < i)
			temp *= 2;
		return temp;
	}

	Texture::Texture(File * file)
		: padding(0)
	{
		file->retain();
		this->file = file;
	}
	
	Texture::~Texture()
	{
		// We're done with the file.
		file->release();

		unload();
	}

	int Texture::getTextureWidth() const
	{
		return textureWidth;
	}

	int Texture::getTextureHeight() const
	{
		return textureHeight;
	}

	int Texture::getWidth() const
	{
		return (int)width;
	}

	int Texture::getHeight() const
	{
		return (int)width;
	}

	int Texture::getPadding() const
	{
		return padding;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	bool Texture::read()
	{
		if(!file->load())
			return false;

		// Generate DevIL image.
		ilGenImages(1, &image);

		// Bind the image.
		ilBindImage(image);

		// Try to load the image.
		ILboolean success = ilLoadL(IL_TYPE_UNKNOWN, (void*)file->getData(), file->getSize());

		// Check for errors
		if(!success)
		{
			std::cerr << "Could not load image \"" << file->getFilename() << "\": " << getErrorString(ilGetError()) << "." << std::endl;
			return false;
		}

		this->width	= (float)ilGetInteger(IL_IMAGE_WIDTH);
		this->height = (float)ilGetInteger(IL_IMAGE_HEIGHT);
		this->origin = ilGetInteger(IL_IMAGE_ORIGIN);

		this->textureWidth = (int)width;
		this->textureHeight = (int)height;

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		return true;
	}

	rgba * Texture::getData() const
	{
		return (rgba *)ilGetData();
	}

	bool Texture::lock()
	{
		padTwoPower();

		// Pass on to OGL
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)textureWidth, (GLsizei)textureHeight, 0, 
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

		// Check for errors
		if(texture == 0) 
			return false;

		return true;
	}

	void Texture::free()
	{
		// Delete DevIL-data (no longer needed)
		ilDeleteImages(1, &image);
		
		// Unload the file.
		file->unload();
	}

	bool Texture::load()
	{	
		// Read file.
		if(!read())
			return false;

		// Send to hardware
		if(!lock())
			return false;

		// Free local data.
		free();

		// HW texture will be removed in unload.
		return true;
	}

	void Texture::unload()
	{
		unloadVolatile();
	}

	bool Texture::loadVolatile()
	{
		// Read file.
		if(!read())
			return false;

		// Send to hardware
		if(!lock())
			return false;

		// Free local data.
		free();

		return true;
	}

	void Texture::unloadVolatile()
	{
		// Delete the hardware texture.
		if(texture != 0)
			glDeleteTextures(1, &texture);
	}

	void Texture::padTwoPower()
	{
		// Bind the image.
		ilBindImage(image);

		// Get twopower of width and height
		ILuint width	= power_of_two((int)this->width);
		ILuint height	= power_of_two((int)this->height);

		// No change needed?
		if(width == this->width && height == this->height)
			return;

		// Get key data
		ILuint depth	= ilGetInteger(IL_IMAGE_DEPTH);
		ILuint bpp		= ilGetInteger(IL_IMAGE_BPP);
		ILuint type		= ilGetInteger(IL_IMAGE_TYPE);
		ILuint format	= ilGetInteger(IL_IMAGE_FORMAT);
		
		// Create new data.
		int size = width * height * bpp;

		// Destination
		rgba * d = new rgba[size];

		// Source
		rgba * s = (rgba *)ilGetData();
		
		for(int i = 0; i<size; i++)
		{
			d[i].r = 0;
			d[i].g = 0;
			d[i].b = 0;
			d[i].a = 0;
		}

		for(int y=0;y<this->height;y++)
		{
			for(int x=0;x<this->width;x++)
			{			
				int si = ((origin == IL_ORIGIN_LOWER_LEFT) ? (int)this->height - y - 1  : y) * (int)this->width + x;
				int di = y * width + x;

				d[di].r = s[si].r;
				d[di].g = s[si].g;
				d[di].b = s[si].b;
				d[di].a = s[si].a;
			}
		}

		// If origin was lower left, it's flipped by now.
		origin = IL_ORIGIN_UPPER_LEFT;

		// Delete the old image.
		ilDeleteImages(1, &image);

		// Generate new DevIL image.
		ilGenImages(1, &image);

		// Bind the image.
		ilBindImage(image);

		// Create the new image
		ilTexImage(width, height, depth, bpp, format, type, (ILvoid*)d);

		// Set new "real" dimensions
		this->textureWidth = width;
		this->textureHeight = height;

		// Cleanup
		delete [] d;
	}

	bool pixel_in_range(rgba * data, int width, int height, int x, int y)
	{
		return (x >= 0 && y >= 0 && x < width && y < height);
	}

	void pixel_commit(rgba & source, int & r, int & g, int & b, int & counter)
	{
		if(source.a != 0)
		{
			counter++;
			r += source.r;
			g += source.g;
			b += source.b;
		}
	}

	void pixel_average_area(rgba * data, int width, int height, int x, int y)
	{
		int p = 0; // Number of neighbor pixels with alpha != 0
		int r = 0, g = 0, b = 0;

		if(pixel_in_range(data, width, height, x-1, y-1)) pixel_commit(data[(y-1)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x, y-1)) pixel_commit(data[(y-1)*width+(x)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y-1)) pixel_commit(data[(y-1)*width+(x+1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x-1, y)) pixel_commit(data[(y)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y)) pixel_commit(data[(y)*width+(x+1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x-1, y+1)) pixel_commit(data[(y+1)*width+(x-1)], r, g, b, p);
		if(pixel_in_range(data, width, height, x, y+1)) pixel_commit(data[(y+1)*width+(x)], r, g, b, p);
		if(pixel_in_range(data, width, height, x+1, y+1))pixel_commit(data[(y+1)*width+(x+1)], r, g, b, p);

		if(p == 0) p = 1;

		data[y*width+x].r = r/p;
		data[y*width+x].g = g/p;
		data[y*width+x].b = b/p;

	}

	void Texture::optimize()
	{
		// Get the width and height of the data.
		int width	= (int)this->width;
		int height	= (int)this->height;

		// Source
		rgba * s = (rgba *)ilGetData();

		for(int y=0;y<this->height;y++)
		{
			for(int x=0;x<this->width;x++)
			{
				if(s[y*width+x].a == 0)
				{
					pixel_average_area(s, width, height, x, y);
				}
			}
		}

	}

	void Texture::pad(int size)
	{

		padding = size;
		
		// Bind the image.
		ilBindImage(image);

		// Get the width and height of the data.
		int old_width	= (int)this->width;
		int old_height	= (int)this->height;

		int new_width = old_width + size*2;
		int new_height = old_height + size*2;

		ILuint bpp = ilGetInteger(IL_IMAGE_BPP);

		// Destination
		int new_size = new_width * new_height * bpp;
		rgba * d = new rgba[new_size];

		// Source
		rgba * s = (rgba *)ilGetData();

		for(int i = 0; i<new_size; i++)
		{
			d[i].r = 0;
			d[i].g = 0;
			d[i].b = 0;
			d[i].a = 0;
		}

		for(int x = 0;x<old_width;x++)
		{
			for(int y = 0;y<old_height;y++)
			{
				int si = ((origin == IL_ORIGIN_LOWER_LEFT) ? old_height - y - 1  : y)*old_width+x;
				int di = (y+size)*new_width+(x+size);
				d[di] = s[si];
			}
		}

		// If origin was lower left, it's flipped by now.
		origin = IL_ORIGIN_UPPER_LEFT;

		// Set the new image data.
		setPixels(d, new_width, new_height);
	}

	void Texture::setPixels(rgba * data, int width, int height)
	{

		// Bind the image.
		ilBindImage(image);

		// Get some image data.
		ILuint depth	= ilGetInteger(IL_IMAGE_DEPTH);
		ILuint bpp		= ilGetInteger(IL_IMAGE_BPP);
		ILuint type		= ilGetInteger(IL_IMAGE_TYPE);
		ILuint format	= ilGetInteger(IL_IMAGE_FORMAT);
		//ILuint origin	= ilGetInteger(IL_IMAGE_ORIGIN);
		
		// Delete the old image.
		ilDeleteImages(1, &image);

		// Generate new DevIL image.
		ilGenImages(1, &image);

		// Bind the new image.
		ilBindImage(image);

		// Create the new image
		ilTexImage(width, height, depth, bpp, format, type, (ILvoid*)data);

		// Set the new image dimensions.
		this->textureWidth = width;
		this->textureHeight = height;
		this->width = (float)width;
		this->height = (float)height;
	}

	const char * Texture::getErrorString(int error)
	{
		switch(error)
		{
		case IL_INVALID_ENUM: return "IL_INVALID_ENUM";
		case IL_OUT_OF_MEMORY: return "IL_OUT_OF_MEMORY";
		case IL_FORMAT_NOT_SUPPORTED: return "IL_FORMAT_NOT_SUPPORTED";
		case IL_INTERNAL_ERROR: return "IL_INTERNAL_ERROR";
		case IL_INVALID_VALUE: return "IL_INVALID_VALUE";
		case IL_ILLEGAL_OPERATION: return "IL_ILLEGAL_OPERATION";
		case IL_ILLEGAL_FILE_VALUE: return "IL_ILLEGAL_FILE_VALUE";
		case IL_INVALID_FILE_HEADER: return "IL_INVALID_FILE_HEADER";
		case IL_INVALID_PARAM: return "IL_INVALID_PARAM";
		case IL_COULD_NOT_OPEN_FILE: return "IL_COULD_NOT_OPEN_FILE";
		case IL_INVALID_EXTENSION: return "IL_INVALID_EXTENSION";
		case IL_FILE_ALREADY_EXISTS: return "IL_FILE_ALREADY_EXISTS";
		case IL_OUT_FORMAT_SAME: return "IL_OUT_FORMAT_SAME";
		case IL_STACK_OVERFLOW: return "IL_STACK_OVERFLOW";
		case IL_STACK_UNDERFLOW: return "IL_STACK_UNDERFLOW";
		case IL_INVALID_CONVERSION: return "IL_INVALID_CONVERSION";
		case IL_BAD_DIMENSIONS: return "IL_BAD_DIMENSIONS";
		case IL_FILE_READ_ERROR: return "IL_FILE_READ_ERROR";
		default:
			return 0;
		}
	}
	
} // opengl
} // love
