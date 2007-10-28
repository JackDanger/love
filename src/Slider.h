#ifndef LOVE_SLIDER_H
#define LOVE_SLIDER_H

#include "AbstractColor.h"
#include "AbstractImage.h"
#include "Font.h"
#include "Text.h"

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

namespace love
{
	/**
	 * @class Slider
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-10-28
	 * @brief A slider used by the Menu.
	 **/
	class Slider : public gcn::Slider
	{
	protected:
		pAbstractColor color;
		pAbstractColor backgroundColor;
		pAbstractColor borderColor;
		pAbstractImage markerImage;
		pAbstractImage backgroundImage;

	public:
		static const int LOVE_SLIDER_VERTICAL = gcn::Slider::VERTICAL;
		static const int LOVE_SLIDER_HORIZONTAL = gcn::Slider::HORIZONTAL;

		Slider(double scaleEnd = 1);
		Slider(double scaleStart, double scaleEnd);
		~Slider();

		virtual void setSize(int width, int height);
		virtual void setWidth(int width);
		virtual void setHeight(int height);
		virtual void setBorderSize(unsigned int size);

		virtual void setScale(double scaleStart, double scaleEnd);
		virtual void setScaleStart(double scaleStart);
		virtual void setScaleEnd(double scaleEnd);
		virtual void setStepLength(double length);
		virtual void setMarkerLength(int length);
		virtual void setOrientation(unsigned int orientation);

		virtual void setValue(double value);
		virtual void setName(const char * name);

		virtual void setColor(const pAbstractColor * color);
		virtual void setBackgroundColor(const pAbstractColor * color);
		virtual void setBorderColor(const pAbstractColor * color);
		virtual void setMarkerImage(const pAbstractImage * image);
		virtual void setBackgroundImage(const pAbstractImage * image);

		virtual int getWidth();
		virtual int getHeight();
		virtual unsigned int getBorderSize();

		virtual double getScaleStart();
		virtual double getScaleEnd();
		virtual double getStepLength();
		virtual int getMarkerLength();
		virtual unsigned int getOrientation();

		virtual double getValue();
		virtual const char * getName();

		virtual void adjustSize();

		virtual void draw(gcn::Graphics * graphics);
		virtual void drawBorder(gcn::Graphics * graphics);
		virtual void drawMarker(gcn::Graphics * graphics);
	};

	typedef boost::shared_ptr<Slider> pSlider;
}

#endif
