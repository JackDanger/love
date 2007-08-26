#ifndef LOVE_GRADIENTCOLOR_H
#define LOVE_GRADIENTCOLOR_H

#include <vector>
#include <math.h>
#include "Object.h"
#include "Color.h"

using std::vector;

namespace love
{
	/**
	 * @class GradientColor
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-08-16
	 * @brief This takes care of all the gradienting of colors.
	 **/
	class GradientColor : public Object
	{
	private:
		vector<Color> colors;
		vector<float> positions;
		Color color1;
		Color color2;

	public:
		GradientColor();
		GradientColor(Color color1, Color color2);
		~GradientColor();

		void add(Color newColor);
		void add(Color newColor, float position);

		Color getColor(float position);
	};

	typedef boost::shared_ptr<GradientColor> pGradientColor;
}

#endif