/**
* @file GUIRadialKnob.h
* @author Anders Ruud
* @date 2007-05-14
* @brief Contains definition for class GUIRadialKnob.
**/

#ifndef LOVE_GUIRADIALKNOB_H
#define LOVE_GUIRADIALKNOB_H

// LOVE
#include "GUIEntity.h"
#include "Text.h"
#include "AbstractImage.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class GUIGameList2;

	/**
	* @class GUIRadialKnob
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-05-14
	* @brief 
	**/
	class GUIRadialKnob : public GUIEntity
	{
	private:


		AbstractImage * big;
		AbstractImage * small;
		Font * font;

		float bigRadius;
		float smallRadius;

		bool lock;

		float clampa(float angle);
		float angle(const Vextor & v1, const Vextor & v2) const;

		GUIGameList2 * control;

	public:

		/**
		* @brief Contructs an empty GUIRadialKnob.
		**/
		GUIRadialKnob(AbstractImage * big, AbstractImage * small, Font * font);
		virtual ~GUIRadialKnob();

		void update(float dt);
		void render();

		void mousePressed(float x, float y, int button);

		void setControl(GUIGameList2 * control);
	};

	typedef boost::shared_ptr<GUIRadialKnob> pGUIRadialKnob;

} // love

#endif

