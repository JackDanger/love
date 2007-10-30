#include "AbstractColor.h"
#include "Color.h"

namespace love
{
	AbstractColor::AbstractColor()
	{
		red = blue = green = alpha = 255;
	}

	AbstractColor::~AbstractColor()
	{
	}

	int AbstractColor::getRed() const
	{
		return red;
	}

	int AbstractColor::getGreen() const
	{
		return green;
	}

	int AbstractColor::getBlue() const
	{
		return blue;
	}

	int AbstractColor::getAlpha() const
	{
		return alpha;
	}

	int AbstractColor::getCode() const
	{
		return (blue | (green << 8) | (red << 16));
	}

	void AbstractColor::setRed(int red)
	{
		this->red = red;
	}

	void AbstractColor::setGreen(int green)
	{
		this->green = green;
	}

	void AbstractColor::setBlue(int blue)
	{
		this->blue = blue;
	}

	void AbstractColor::setAlpha(int alpha)
	{
		this->alpha = alpha;
	}

	void AbstractColor::setColor(int code)
	{
		red = (code & 0xFF0000) >> 16;
		green = (code & 0x00FF00) >> 8;
		blue = code & 0x0000FF;
	}

	void AbstractColor::setColor(int red, int green, int blue)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
	}

	void AbstractColor::setColor(int red, int green, int blue, int alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}

	boost::shared_ptr<AbstractColor> AbstractColor::getColor()
	{
		boost::shared_ptr<AbstractColor> temp (this);
		return temp;
	}

	boost::shared_ptr<AbstractColor> AbstractColor::getColor(float time)
	{
		return getColor();
	}

	boost::shared_ptr<AbstractColor> AbstractColor::getGradient(const boost::shared_ptr<AbstractColor> * other, float amount)
	{
		boost::shared_ptr<AbstractColor> temp (new Color());
		temp->setRed((int)((*other)->getRed() + ((this->red - (*other)->getRed()) * amount)));
		temp->setGreen((int)((*other)->getGreen() + ((this->green - (*other)->getGreen()) * amount)));
		temp->setBlue((int)((*other)->getBlue() + ((this->blue - (*other)->getBlue()) * amount)));
		temp->setAlpha((int)((*other)->getAlpha() + ((this->alpha - (*other)->getAlpha()) * amount)));
		return temp;
	}

	void AbstractColor::addColor(const pAbstractColor * color, float time)
	{}

	void AbstractColor::addColor(int r, int g, int b, int a, float time)
	{}

	void AbstractColor::setMode(int mode)
	{}

	void AbstractColor::play()
	{}

	void AbstractColor::stop()
	{}
	
	void AbstractColor::reset()
	{}
}
