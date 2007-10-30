#include "Slider.h"

namespace love
{
	Slider::Slider(double scaleEnd) : gcn::Slider(scaleEnd)
	{
	}

	Slider::Slider(double scaleStart, double scaleEnd) : gcn::Slider(scaleStart, scaleEnd)
	{
	}

	Slider::~Slider()
	{
	}

	void Slider::setSize(int width, int height)
	{
		gcn::Slider::setSize(width, height);
	}

	void Slider::setWidth(int width)
	{
		gcn::Slider::setWidth(width);
	}

	void Slider::setHeight(int height)
	{
		gcn::Slider::setHeight(height);
	}

	void Slider::setBorderSize(unsigned int size)
	{
		gcn::Slider::setBorderSize(size);
	}

	void Slider::setScale(double scaleStart, double scaleEnd)
	{
		gcn::Slider::setScale(scaleStart, scaleEnd);
	}

	void Slider::setScaleStart(double scaleStart)
	{
		gcn::Slider::setScaleStart(scaleStart);
	}

	void Slider::setScaleEnd(double scaleEnd)
	{
		gcn::Slider::setScaleEnd(scaleEnd);
	}

	void Slider::setStepLength(double length)
	{
		gcn::Slider::setStepLength(length);
	}
	
	void Slider::setMarkerLength(int length)
	{
		gcn::Slider::setMarkerLength(length);
	}

	void Slider::setOrientation(unsigned int orientation)
	{
		gcn::Slider::setOrientation(orientation);
	}

	void Slider::setValue(double value)
	{
		gcn::Slider::setValue(value);
	}

	void Slider::setName(const char * name)
	{
		gcn::Slider::setActionEventId(name);
	}

	void Slider::setMarkerImage(const pAbstractImage * image)
	{
		markerImage = (*image);
		setMarkerLength((int)markerImage->getWidth());
	}

	void Slider::setBackgroundImage(const pAbstractImage * image)
	{
		backgroundImage = (*image);
	}

	int Slider::getWidth()
	{
		return gcn::Slider::getWidth();
	}

	int Slider::getHeight()
	{
		return gcn::Slider::getHeight();
	}

	unsigned int Slider::getBorderSize()
	{
		return gcn::Slider::getBorderSize();
	}

	double Slider::getScaleStart()
	{
		return gcn::Slider::getScaleStart();
	}

	double Slider::getScaleEnd()
	{
		return gcn::Slider::getScaleEnd();
	}

	double Slider::getStepLength()
	{
		return gcn::Slider::getStepLength();
	}

	int Slider::getMarkerLength()
	{
		return gcn::Slider::getMarkerLength();
	}

	unsigned int Slider::getOrientation()
	{
		return gcn::Slider::getOrientation();
	}

	double Slider::getValue()
	{
		return gcn::Slider::getValue();
	}

	const char * Slider::getName()
	{
		return gcn::Slider::getActionEventId().c_str();
	}

	void Slider::adjustSize()
	{
		if(backgroundImage.get() != 0)
		{
			if(getWidth() < backgroundImage->getWidth())
				setWidth((int)backgroundImage->getWidth());
			if(getHeight() < backgroundImage->getHeight())
				setHeight((int)backgroundImage->getHeight());
		}
	}

	void Slider::draw(gcn::Graphics * graphics)
	{
		if(backgroundImage.get() != 0)
		{
			int x = (int)((getWidth() / 2) - (backgroundImage->getWidth() / 2));
			int y = (int)((getHeight() / 2) - (backgroundImage->getHeight() / 2));

			backgroundImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
			drawMarker(graphics);
		}
		else
		{
			if(color.get() != 0)
			{
				setBaseColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
				setForegroundColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
			}
			if(backgroundColor.get() != 0)
				setBaseColor(gcn::Color(backgroundColor->getRed(), backgroundColor->getGreen(), backgroundColor->getBlue(), backgroundColor->getAlpha()));

			gcn::Slider::draw(graphics);
		}
	}

	void Slider::drawBorder(gcn::Graphics * graphics)
	{
		if(color.get() != 0)
			setBaseColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));
		if(borderColor.get() != 0)
			setBaseColor(gcn::Color(borderColor->getRed(), borderColor->getGreen(), borderColor->getBlue(), borderColor->getAlpha()));

		gcn::Slider::drawBorder(graphics);
	}

	void Slider::drawMarker(gcn::Graphics * graphics)
	{
		if(markerImage.get() != 0)
		{
			int x = 0;
			int y = 0;
			switch(getOrientation())
			{
			default:
			case LOVE_SLIDER_HORIZONTAL:
				x = getMarkerPosition();
				y = (int)((getHeight() / 2) - (markerImage->getHeight() / 2));
				break;
			case LOVE_SLIDER_VERTICAL:
				x = (int)((getWidth() / 2) - (markerImage->getWidth() / 2));
				y = getMarkerPosition();
				break;
			}
			markerImage->render((float)graphics->getCurrentClipArea().x + x, (float)graphics->getCurrentClipArea().y + y);
		}
		else
		{
			if(color.get() != 0)
				setBaseColor(gcn::Color(color->getRed(), color->getGreen(), color->getBlue(), color->getAlpha()));

			gcn::Slider::drawMarker(graphics);
		}
	}
}