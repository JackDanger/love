#include "Animation.h"

#include <cmath>

namespace love_opengl
{
	Animation::Animation(pImage image) : image(image), mode(1), current(0), playing(true),
		timeBuffer(0), direction(1), speed(1.0f)
	{
	}

	Animation::Animation(pImage image, float fw, float fh, float delay, int num) : 
	image(image), mode(1), current(0), playing(true), timeBuffer(0), direction(1), speed(1.0f)
	{
		// Generate frames.
		int w = (int)(image->getWidth()/fw);
		int h = (int)(image->getHeight()/fh);

		int real_num = (num == 0) ? (w * h) : num;
		if(real_num > (w * h)) real_num = (w * h);

		for(int i = 0;i<real_num;i++)
		{
			int x = (int)((i % w)*fw);
			int y = (int)((i/w)*fh);

			addFrame((float)x, (float)y, fw, fh, delay);
		}
	}

	Animation::~Animation()
	{
	}

	void Animation::addFrame(float x, float y, float w, float h, float delay)
	{
		// Add delay.
		delays.push_back(delay);

		// Add frame.
		frame f;
		f.x = x; f.y = y;
		f.width = w;
		f.height = h;
		f.post_delay = (int)delays.size() - 1;
		
		float xTex = x/(float)image->getTextureWidth();
		float yTex = y/(float)image->getTextureHeight();

		float wTex = w/(float)image->getTextureWidth();
		float hTex = h/(float)image->getTextureHeight();

		f.vertices[0] = 0; f.vertices[1] = 0;
		f.vertices[2] = 0; f.vertices[3] = floor(h);
		f.vertices[4] = floor(w); f.vertices[5] = floor(h);
		f.vertices[6] = floor(w); f.vertices[7] = 0;

		f.texels[0] = xTex; f.texels[1] = yTex;
		f.texels[2] = xTex; f.texels[3] = yTex+hTex;
		f.texels[4] = xTex+wTex; f.texels[5] = yTex+hTex;
		f.texels[6] = xTex+wTex; f.texels[7] = yTex;

		frames.push_back(f);
		
		if(frames.size() > 1)
		{
			frames.back().pre_delay = frames[frames.size() - 2].post_delay;

			// Update delay of first frame.
			frames.front().pre_delay = frames.back().post_delay;
		}

	}

	void Animation::setMode(int mode)
	{
		this->mode = mode;
	}

	void Animation::play()
	{
		playing = true;
	}

	void Animation::stop()
	{
		playing = false;
	}

	void Animation::reset()
	{
		current = 0;
		timeBuffer = 0;
	}

	void Animation::seek(int frame)
	{
		if(frame >= 0 && frame < (int)frames.size())
			current = frame;
	}

	int Animation::getCurrentFrame() const
	{
		return current;
	}

	int Animation::getSize() const
	{
		return (int)frames.size();
	}

	void Animation::setDelay(int frame, float delay)
	{
		if(frame >= 0 && frame < (int)frames.size())
			delays[frames[0].post_delay] = delay;
	}

	void Animation::setSpeed(float speed)
	{
		this->speed = speed;
	}

	float Animation::getSpeed() const
	{
		return speed;
	}

	void Animation::bind() const
	{
		image->bind();
	}

	void Animation::update(float dt)
	{
		if(!playing)
			return;
		
		if(frames.size() <= 0)
			return;

		timeBuffer += (dt * speed);

		int next;
		float d;

		switch(mode)
		{
		case love::ANIMATION_LOOP:
			next = current;
			while(timeBuffer >= delays[frames[current].post_delay])
			{
				timeBuffer -= delays[frames[current].post_delay];
				if(++next >= (int)frames.size())
					next = 0;
			}
			current = next;
			break;
		case love::ANIMATION_PLAY_ONCE:
			next = current;
			while(timeBuffer >= delays[frames[current].post_delay])
			{
				timeBuffer -= delays[frames[current].post_delay];
				if(++next >= (int)frames.size())
				{
					next--;
					playing = false;
					timeBuffer = 0;
				}
			}
			current = next;
			break;
		case love::ANIMATION_BOUNCE:
			next = current;
			d = (direction == 1) ? delays[frames[next].post_delay] : delays[frames[next].pre_delay];

			while(timeBuffer >= d)
			{
				timeBuffer -= d;
				next += direction;
				if(next < 0 || next >= (int)frames.size())
				{
					direction *= -1;
					next += direction;
				}
				d = (direction == 1) ? delays[frames[next].post_delay] : delays[frames[next].pre_delay];
			}
			current = next;
			break;
		}

		// Set the current width/height.
		this->width = frames[current].width;
		this->height = frames[current].height;
	}

	void Animation::draw(float x, float y) const
	{
		if(frames.size() <= 0)
			return;

		const frame & f = frames[current];
		image->draw(f.vertices, f.texels, x, y, 0, 1, 1, -f.width/2.0f + center_x, -f.height/2.0f + center_y, love::FLIP_NONE);
	}

	void Animation::draw(float x, float y, float angle, float sx, float sy, int flip) const
	{
		if(frames.size() <= 0)
			return;

		const frame & f = frames[current];
		image->draw(f.vertices, f.texels, x, y, angle, sx, sy, -f.width/2.0f + center_x, -f.height/2.0f + center_y, flip);
	}
} // love_opengl
