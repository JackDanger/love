/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* A Chipmunk 2D wrapper. Provides 2D physics and
* fun for everyone in the family.
* 
* @author Anders Ruud
* @date 2008-03-21
*/
#ifndef LOVE_MOD_CHIPMUNK_H
#define LOVE_MOD_CHIPMUNK_H

// LOVE
#include <love/mod.h>

// Module.
#include "Space.h"
#include "Body.h"
#include "Shape.h"

#include "CircleShape.h"
#include "PolygonShape.h"
#include "SegmentShape.h"

#include "PinJoint.h"
#include "SlideJoint.h"
#include "PivotJoint.h"
#include "GrooveJoint.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_chipmunk
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	int collision(cpShape * a, cpShape * b, cpContact * contacts, 
		int numContacts, cpFloat normal_coef, void *data);

	pSpace newSpace();
	pBody newBody(pSpace space, float x, float y, float m, float i);
	pBody newStaticBody(pSpace space, float x, float y, float m, float i);
	pShape newCircle(pBody body, float radius);
	pSegmentShape newSegment(pBody body, float x1, float y1, float x2, float y2);
	pPinJoint newPin(pBody body1, pBody body2, float x1, float y1, float x2, float y2);
	pSlideJoint newSlide(pBody body1, pBody body2, float x1, float y1, float x2, float y2, float min, float max);
	pPivotJoint newPivot(pBody body1, pBody body2, float x, float y);
	pGrooveJoint newGroove(pBody body1, pBody body2, float x1, float y1, float x2, float y2, float x3, float y3);

	//
	// Native functions.
	//

	int newPolygon(lua_State * L);

	//void dampedSpring(pBody & a, pBody & b, const pVector & anchr1, const pVector & anchr2, 
	//	float rlen, float k, float dmp, float dt);

} // love_chipmunk

#endif // LOVE_MOD_CHIPMUNK_H
