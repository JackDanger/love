/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* @author Anders Ruud
* @date 2008-01-19
**/

#include "Animation.h"

// LOVE
#include "../liblove/constants.h"

// STD
#include <cmath>

namespace love
{
namespace opengl
{
	Animation::Animation(Image * image) 
		: image(image), mode(1), current(0), playing(true),
		timeBuffer(0), direction(1), speed(1.0f)
	{
		image->retain();
	}

	Animation::Animation(Image * image, float fw, float fh, float delay, int num) 
		: image(image), mode(1), current(0), playing(true), timeBuffer(0), direction(1), speed(1.0f)
	{
		
		image->retain();

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
		for(int i = 0;i<(int)frames.size();i++)
		{
			if(frames[i].image != 0)
			{
				frames[i].image->release();
				frames[i].image = 0;
			}
		}

		if(image != 0)
			image->release();
	}

	void Animation::addFrame(float x, float y, float w, float h, float delay)
	{
		// Add delay.
		delays.push_back(delay);

		// Add frame.
		AnimationFrame f;
		f.image = new Image(image, x, y, w, h);
		f.image->setOffset(offsetX, offsetY);
		f.postDelay = (int)delays.size() - 1;

		frames.push_back(f);
		
		if(frames.size() > 1)
		{
			frames.back().preDelay = frames[frames.size() - 2].postDelay;

			// Update delay of first frame.
			frames.front().preDelay = frames.back().postDelay;
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
			delays[frames[0].postDelay] = delay;
	}

	void Animation::setSpeed(float speed)
	{
		this->speed = speed;
	}

	float Animation::getSpeed() const
	{
		return speed;
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
		case ANIMATION_LOOP:
			next = current;
			while(timeBuffer >= delays[frames[current].postDelay])
			{
				timeBuffer -= delays[frames[current].postDelay];
				if(++next >= (int)frames.size())
					next = 0;
			}
			current = next;
			break;
		case ANIMATION_PLAY_ONCE:
			next = current;
			while(timeBuffer >= delays[frames[current].postDelay])
			{
				timeBuffer -= delays[frames[current].postDelay];
				if(++next >= (int)frames.size())
				{
					next--;
					playing = false;
					timeBuffer = 0;
				}
			}
			current = next;
			break;
		case ANIMATION_BOUNCE:
			next = current;
			d = (direction == 1) ? delays[frames[next].postDelay] : delays[frames[next].preDelay];

			while(timeBuffer >= d)
			{
				timeBuffer -= d;
				next += direction;
				if(next < 0 || next >= (int)frames.size())
				{
					direction *= -1;
					next += direction;
				}
				d = (direction == 1) ? delays[frames[next].postDelay] : delays[frames[next].preDelay];
			}
			current = next;
			break;
		}
	}

	void Animation::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		if(frames.size() <= 0)
			return;

		const AnimationFrame & f = frames[current];
		f.image->draw(x, y, angle, sx, sy, float ox, float oy);
	}

} // opengl
} // love
