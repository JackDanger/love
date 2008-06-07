#include "Image.h"

// STD
#include <cmath>
using std::string;

// SDL
#include "GLee.h"
#include <SDL_opengl.h>

// DevIL
#include <IL/ilut.h>

namespace love_opengl
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

	Image::Image(love::pFile file) : love::Resource(file), padding(0), image(0), texture(0)
	{
	}
	
	Image::~Image()
	{
		unload();
	}

	int Image::getTextureWidth() const
	{
		return textureWidth;
	}

	int Image::getTextureHeight() const
	{
		return textureHeight;
	}

	int Image::getPadding() const
	{
		return padding;
	}

	void Image::draw() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex2i(0,0);
			glTexCoord2f(0.0,1.0); glVertex2i(0,textureHeight);
			glTexCoord2f(1.0,1.0); glVertex2i(textureWidth,textureHeight);
			glTexCoord2f(1.0,0.0); glVertex2i(textureWidth,0);
		glEnd();
		
	}

	void Image::draw(float x, float y) const
	{
		glPushMatrix();
		glTranslatef(x, y, 0);
		glTranslatef(-center_x-padding, -center_y-padding, 0);
		draw();
		glPopMatrix();
	}

	void Image::draws(float x, float y, float w, float h) const
	{

		glBindTexture(GL_TEXTURE_2D,texture);

		float xTex = x/(float)textureWidth;
		float yTex = y/(float)textureHeight;

		float wTex = w/(float)textureWidth;
		float hTex = h/(float)textureHeight;

		glBegin(GL_QUADS);
			glTexCoord2f(xTex,yTex);				glVertex2f(0,0);
			glTexCoord2f(xTex,yTex+hTex);			glVertex2f(0,h);
			glTexCoord2f(xTex+wTex,yTex+hTex);		glVertex2f(w,h);
			glTexCoord2f(xTex+wTex,yTex);			glVertex2f(w,0);
		glEnd();
	}

	void Image::draw(float x, float y, float angle, float sx, float sy, int flip) const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(-center_x-padding, -center_y-padding, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(texels[flipmap[flip][0]], texels[flipmap[flip][1]]); glVertex2i(0,0);
			glTexCoord2f(texels[flipmap[flip][2]], texels[flipmap[flip][3]]); glVertex2i(0,textureHeight);
			glTexCoord2f(texels[flipmap[flip][4]], texels[flipmap[flip][5]]); glVertex2i(textureWidth,textureHeight);
			glTexCoord2f(texels[flipmap[flip][6]], texels[flipmap[flip][7]]); glVertex2i(textureWidth,0);
		glEnd();
		glPopMatrix();
	}

	void Image::draw(const float * vertices, const float * texels, float x, float y, 
		float angle, float sx, float sy, float ox, float oy, int flip) const
	{
		glBindTexture(GL_TEXTURE_2D,texture);

		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(ox, oy, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(texels[flipmap[flip][0]], texels[flipmap[flip][1]]); glVertex2f(vertices[0],vertices[1]);
			glTexCoord2f(texels[flipmap[flip][2]], texels[flipmap[flip][3]]); glVertex2f(vertices[2],vertices[3]);
			glTexCoord2f(texels[flipmap[flip][4]], texels[flipmap[flip][5]]); glVertex2f(vertices[4],vertices[5]);
			glTexCoord2f(texels[flipmap[flip][6]], texels[flipmap[flip][7]]); glVertex2f(vertices[6],vertices[7]);
		glEnd();
		glPopMatrix();
	}

	void Image::draws(float x, float y, float cx, float cy, float w, float h, float angle,
				float sx, float sy, float ox, float oy ,int flip) const
	{
		float xTex = cx/(float)textureWidth;
		float yTex = cy/(float)textureHeight;
		float wTex = w/(float)textureWidth;
		float hTex = h/(float)textureHeight;

		const float texels[] = {
			xTex, yTex, 
			xTex, yTex+hTex, 
			xTex+wTex, yTex+hTex,
			xTex+wTex, yTex 
		};

		glBindTexture(GL_TEXTURE_2D,texture);

		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 0, 1.0f);
		glScalef(sx, sy, 1.0f);
		glTranslatef(ox, oy, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(texels[flipmap[flip][0]], texels[flipmap[flip][1]]); glVertex2f(0,0);
			glTexCoord2f(texels[flipmap[flip][2]], texels[flipmap[flip][3]]); glVertex2f(0,h);
			glTexCoord2f(texels[flipmap[flip][4]], texels[flipmap[flip][5]]); glVertex2f(w,h);
			glTexCoord2f(texels[flipmap[flip][6]], texels[flipmap[flip][7]]); glVertex2f(w,0);
		glEnd();
		glPopMatrix();
	}


	void Image::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,texture);
	}

	bool Image::read()
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
			printf((const char *)iluErrorString(ilGetError()));

		this->width	= (float)ilGetInteger(IL_IMAGE_WIDTH);
		this->height = (float)ilGetInteger(IL_IMAGE_HEIGHT);
		this->origin = ilGetInteger(IL_IMAGE_ORIGIN);

		center_x = this->width/2.0f;
		center_y = this->height/2.0f;

		this->textureWidth = (int)width;
		this->textureHeight = (int)height;

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		return true;
	}

	rgba * Image::getData() const
	{
		return (rgba *)ilGetData();
	}

	void Image::update(float dt)
	{

	}

	bool Image::lock()
	{
		padTwoPower();

		// Pass on to OGL
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// @todo Warning. GL_RGBA8 might fail.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)textureWidth, (GLsizei)textureHeight, 0, 
			ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());

		// Check for errors
		if(texture == 0) 
			return false;
		

		// Create texture coordinates.
		texels[0] = 0;
		texels[1] = 0;
		texels[2] = 0;
		texels[3] = 1;
		texels[4] = 1;
		texels[5] = 1;
		texels[6] = 1;
		texels[7] = 0;

		// Create texture coordinates.
		vertices[0] = 0;
		vertices[1] = 0;
		vertices[2] = 0;
		vertices[3] = (float)textureHeight;
		vertices[4] = (float)textureWidth;
		vertices[5] = (float)textureHeight;
		vertices[6] = (float)textureWidth;
		vertices[7] = 0;

		return true;
	}

	void Image::free()
	{
		// Delete DevIL-data (no longer needed)
		ilDeleteImages(1, &image);
		
		// Unload the file.
		file->unload();
	}

	bool Image::load()
	{	
		return loadVolatile();
	}

	void Image::unload()
	{
		unloadVolatile();
	}

	bool Image::loadVolatile()
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

	void Image::unloadVolatile()
	{
		// Delete the hardware texture.
		if(texture != 0)
			glDeleteTextures(1, &texture);
	}

	void Image::padTwoPower()
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

	void Image::optimize()
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

	void Image::pad(int size)
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

	void Image::setPixels(rgba * data, int width, int height)
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
	
} // love
