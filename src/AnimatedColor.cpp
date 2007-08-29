#include "AnimatedColor.h"
#include "Color.h"

namespace love
{
	AnimatedColor::AnimatedColor()
	{
		//current = Color(0xFFFFFF);
		red = blue = green = alpha = 255;
		total = 0;
		elapsed = 0;
		mode = LOVE_ANIMATED_COLOR_LOOP;
		active = false;
		direction = true;
	}

	AnimatedColor::~AnimatedColor()
	{
	}

	void AnimatedColor::loop(float dt)
	{
		elapsed += dt;

		if(elapsed > total)
			elapsed -= total;

		//get what would be the current color
		float temp = 0; int cur = 0;
		for(unsigned int i = 0; i != times.size(); i++)
		{
			temp += times[i];
			if(temp >= elapsed)
			{
				cur = i;
				break;
			}
		}

		temp = (temp - elapsed) / times[cur];

		temp = map(temp);

		int next = cur;
		if(cur == (int)colors.size() - 1)
			next = 0;
		else
			next = next + 1;

		//int red, green, blue, alpha;
		red = (int)(colors[next]->getRed() + ((colors[cur]->getRed() - colors[next]->getRed()) * temp));
		green = (int)(colors[next]->getGreen() + ((colors[cur]->getGreen() - colors[next]->getGreen()) * temp));
		blue = (int)(colors[next]->getBlue() + ((colors[cur]->getBlue() - colors[next]->getBlue()) * temp));
		alpha = (int)(colors[next]->getAlpha() + ((colors[cur]->getAlpha() - colors[next]->getAlpha()) * temp));

		//current.setColor(red, green, blue, alpha);
	}

	void AnimatedColor::play_once(float dt)
	{
		elapsed += dt;

		if(elapsed > (total - times[times.size()-1]))
		{
			red = colors[colors.size()-1]->getRed();
			green = colors[colors.size()-1]->getGreen();
			blue = colors[colors.size()-1]->getBlue();
			alpha = colors[colors.size()-1]->getAlpha();
			stop();
			return;
		}

		//get what would be the current color
		float temp = 0; int cur = 0;
		for(unsigned int i = 0; i != times.size(); i++)
		{
			temp += times[i];
			if(temp >= elapsed)
			{
				cur = i;
				break;
			}
		}

		temp = (temp - elapsed) / times[cur];

		temp = map(temp);

		int next = cur;
		if(cur == (int)colors.size() - 1)
			next = 0;
		else
			next = next + 1;

		//int red, green, blue, alpha;
		red = (int)(colors[next]->getRed() + ((colors[cur]->getRed() - colors[next]->getRed()) * temp));
		green = (int)(colors[next]->getGreen() + ((colors[cur]->getGreen() - colors[next]->getGreen()) * temp));
		blue = (int)(colors[next]->getBlue() + ((colors[cur]->getBlue() - colors[next]->getBlue()) * temp));
		alpha = (int)(colors[next]->getAlpha() + ((colors[cur]->getAlpha() - colors[next]->getAlpha()) * temp));

		//current.setColor(red, green, blue, alpha);
	}

	void AnimatedColor::bounce(float dt)
	{
		if(direction)
		{
			elapsed += dt;
			if(elapsed > (total - times[times.size()-1]))
			{
				direction = false;
				elapsed = total - (elapsed - (total - times[times.size()-1]));
			}
		}
		else
		{
			elapsed -= dt;
			if(elapsed < times[0])
			{
				direction = true;
				elapsed = times[0] - elapsed;
			}
		}

		//get what would be the current color
		float temp = 0; int cur = 0;

		for(unsigned int i = 0; i != times.size(); i++)
		{
			temp += times[i];
			if(temp >= elapsed)
			{
				cur = i;
				break;
			}
		}

		temp = (temp - elapsed) / times[cur];

		temp = map(temp);

		int next = cur;
		if(direction)
		{
			if(cur == (int)colors.size() - 1)
				next = 0;
			else
				next = next + 1;
		}
		else
		{
			cur -= 1;
		}

		//int red, green, blue, alpha;
		red = (int)(colors[next]->getRed() + ((colors[cur]->getRed() - colors[next]->getRed()) * temp));
		green = (int)(colors[next]->getGreen() + ((colors[cur]->getGreen() - colors[next]->getGreen()) * temp));
		blue = (int)(colors[next]->getBlue() + ((colors[cur]->getBlue() - colors[next]->getBlue()) * temp));
		alpha = (int)(colors[next]->getAlpha() + ((colors[cur]->getAlpha() - colors[next]->getAlpha()) * temp));

		//current.setColor(red, green, blue, alpha);
	}

	float AnimatedColor::map(float t)
	{
		return t;
	}

	void AnimatedColor::addColor(const pColor * color, float time)
	{
		if(colors.size() == 0)
		{
			red = (*color)->getRed();
			green = (*color)->getGreen();
			blue = (*color)->getBlue();
			alpha = (*color)->getAlpha();
		}

		colors.push_back((*color));
		times.push_back(time);

		total = 0;
		for(unsigned int i = 0; i < times.size(); i++)
			total += times[i];
	}

	void AnimatedColor::addColor(int r, int g, int b, int a, float time)
	{
		if(colors.size() == 0)
		{
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}

		pColor clr(new Color(r, g, b, a));
		colors.push_back(clr);
		times.push_back(time);

		total = 0;
		for(unsigned int i = 0; i < times.size(); i++)
			total += times[i];
	}

	Color AnimatedColor::getColor()
	{
		Color temp = Color(red, green, blue, alpha);
		return temp;
	}

	Color AnimatedColor::getColor(float time)
	{
		//clamp t
		time = (time < 0) ? 0 : time;
		time = (time > 1) ? 1 : time;

		Color color = Color(0,0,0,0);
		float temp = 0;
		float elap = 0;
		int cur = 0;
		int next = 0;

		for(unsigned int i = 0; i != times.size(); i++)
		{
			elap += times[i];
		}
		elap *= time; //this will get the emulated elapsed time

		for(unsigned int i = 0; i != times.size(); i++)
		{
			temp += times[i];
			if(temp >= elap)
			{
				cur = i;
				break;
			}
		}

		temp = (temp - elap) / times[cur];

		temp = map(temp);

		next = cur;
		if(cur == (int)colors.size() - 1)
			next = next;
		else
			next = next + 1;

		//int red, green, blue, alpha;
		color.setRed( (int)(colors[next]->getRed() + ((colors[cur]->getRed() - colors[next]->getRed()) * temp)) );
		color.setGreen( (int)(colors[next]->getGreen() + ((colors[cur]->getGreen() - colors[next]->getGreen()) * temp)) );
		color.setBlue( (int)(colors[next]->getBlue() + ((colors[cur]->getBlue() - colors[next]->getBlue()) * temp)) );
		color.setAlpha( (int)(colors[next]->getAlpha() + ((colors[cur]->getAlpha() - colors[next]->getAlpha()) * temp)) );

		return color;
	}

	void AnimatedColor::setMode(int mode)
	{
		this->mode = mode;
	}

	void AnimatedColor::play()
	{
		active = true;
	}

	void AnimatedColor::stop()
	{
		active = false;
		//reset();
	}

	void AnimatedColor::reset()
	{
		elapsed = 0;
		if(colors.size() != 0)
		{
			red = colors[0]->getRed();
			green = colors[0]->getGreen();
			blue = colors[0]->getBlue();
			alpha = colors[0]->getAlpha();
		}
		direction = true;
	}

	void AnimatedColor::update(float dt)
	{
		if(colors.size() == 1) //only one color?
		{
			red = colors[0]->getRed(); //then no gradient for you
			green = colors[0]->getGreen();
			blue = colors[0]->getBlue();
			alpha = colors[0]->getAlpha();
			return;
		}

		if(!active && colors.size() == 0)
			return;

		switch(mode)
		{
		case LOVE_ANIMATED_COLOR_LOOP:
			loop(dt);
			break;
		case LOVE_ANIMATED_COLOR_PLAY_ONCE:
			play_once(dt);
			break;
		case LOVE_ANIMATED_COLOR_BOUNCE:
			bounce(dt);
			break;
		default:
			loop(dt);
		}
	}

	void AnimatedColor::setColor(float t)
	{
		// Clamp t
		t = (t < 0) ? 0 : t;
		t = (t > 1) ? 1 : t;

		if(t == 1.0f)
		{
			this->red = colors.back()->getRed();
			this->green = colors.back()->getRed();
			this->blue = colors.back()->getRed();
			this->alpha = colors.back()->getRed();
			return;
		}

		// This t value corresponds to this much time
		float total = (this->total - times[times.size()-1]);
		float time = total * t;
		float min = 0;
		float max = 0;

		// Which color segment are we on?

		int size = (int)times.size() - 1;

		for(int i=0;i<size;i++)
		{
			max += times[i];
			
			if(time >= min && time <= max)
			{
				// Found it ... find dt for this color segment
				float dt = time/max;

				// Calculate color
				this->red = (int)(colors[i]->getRed() + (colors[i+1]->getRed() - colors[i]->getRed()) * dt);
				this->green = (int)(colors[i]->getGreen() + (colors[i+1]->getGreen() - colors[i]->getGreen()) * dt);
				this->blue = (int)(colors[i]->getBlue() + (colors[i+1]->getBlue() - colors[i]->getBlue()) * dt);
				this->alpha = (int)(colors[i]->getAlpha() + (colors[i+1]->getAlpha() - colors[i]->getAlpha()) * dt);

				return;
			}

			min = max;

		}

	}
}
