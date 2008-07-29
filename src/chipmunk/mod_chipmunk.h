/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This file was AUTOGENERATED by swigfusion! Please
* do not edit this file manually.
* 
* @author Anders Ruud / swigfusion
* @date 2008-07-29
**/

#ifndef LOVE_MOD_FUSION_CHIPMUNK_H
#define LOVE_MOD_FUSION_CHIPMUNK_H

#include <boost/shared_ptr.hpp>

// Function from SWIG which opens the module.
extern "C" {
    int luaopen_mod_chipmunk(lua_State * L);
}

// Types found:
// SlideJoint (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__SlideJoint_t)
// Space (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__Space_t)
// PinJoint (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__PinJoint_t)
// Body (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__Body_t)
// SegmentShape (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__SegmentShape_t)
// PolygonShape (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__PolygonShape_t)
// Vector (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__Vector_t)
// PivotJoint (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__PivotJoint_t)
// Joint (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__Joint_t)
// CircleShape (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__CircleShape_t)
// Shape (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__Shape_t)
// GrooveJoint (SWIGTYPE_p_boost__shared_ptrT_love_chipmunk__GrooveJoint_t)

// Fused: 
// CircleShape:setData => _CircleShape_setData
// CircleShape:getPoint => _CircleShape_getPoint,
// CircleShape:getData => _CircleShape_getData
// SegmentShape:setData => _SegmentShape_setData
// SegmentShape:getPoints => _SegmentShape_getPoints
// SegmentShape:getData => _SegmentShape_getData
// PolygonShape:getTransformedPoints => _PolygonShape_getTransformedPoints
// PolygonShape:getData => _PolygonShape_getData
// PolygonShape:setData => _PolygonShape_setData
// PinJoint:getPoints => _PinJoint_getPoints
// SlideJoint:getPoints => _SlideJoint_getPoints
// SlideJoint:getLimits => _SlideJoint_getLimits
// PivotJoint:getPoint => _PivotJoint_getPoint
// GrooveJoint:getPoints => _GrooveJoint_getPoints

namespace love_chipmunk
{

	//Forward declarations.
	class SlideJoint;
	class Space;
	class PinJoint;
	class Body;
	class SegmentShape;
	class PolygonShape;
	class Vector;
	class PivotJoint;
	class Joint;
	class CircleShape;
	class Shape;
	class GrooveJoint;

	bool mod_is_slidejoint(lua_State * L, int idx);
	boost::shared_ptr<SlideJoint> mod_to_slidejoint(lua_State * L, int idx);
	void mod_push_slidejoint(lua_State * L, boost::shared_ptr<SlideJoint> slidejoint);

	bool mod_is_space(lua_State * L, int idx);
	boost::shared_ptr<Space> mod_to_space(lua_State * L, int idx);
	void mod_push_space(lua_State * L, boost::shared_ptr<Space> space);

	bool mod_is_pinjoint(lua_State * L, int idx);
	boost::shared_ptr<PinJoint> mod_to_pinjoint(lua_State * L, int idx);
	void mod_push_pinjoint(lua_State * L, boost::shared_ptr<PinJoint> pinjoint);

	bool mod_is_body(lua_State * L, int idx);
	boost::shared_ptr<Body> mod_to_body(lua_State * L, int idx);
	void mod_push_body(lua_State * L, boost::shared_ptr<Body> body);

	bool mod_is_segmentshape(lua_State * L, int idx);
	boost::shared_ptr<SegmentShape> mod_to_segmentshape(lua_State * L, int idx);
	void mod_push_segmentshape(lua_State * L, boost::shared_ptr<SegmentShape> segmentshape);

	bool mod_is_polygonshape(lua_State * L, int idx);
	boost::shared_ptr<PolygonShape> mod_to_polygonshape(lua_State * L, int idx);
	void mod_push_polygonshape(lua_State * L, boost::shared_ptr<PolygonShape> polygonshape);

	bool mod_is_vector(lua_State * L, int idx);
	boost::shared_ptr<Vector> mod_to_vector(lua_State * L, int idx);
	void mod_push_vector(lua_State * L, boost::shared_ptr<Vector> vector);

	bool mod_is_pivotjoint(lua_State * L, int idx);
	boost::shared_ptr<PivotJoint> mod_to_pivotjoint(lua_State * L, int idx);
	void mod_push_pivotjoint(lua_State * L, boost::shared_ptr<PivotJoint> pivotjoint);

	bool mod_is_joint(lua_State * L, int idx);
	boost::shared_ptr<Joint> mod_to_joint(lua_State * L, int idx);
	void mod_push_joint(lua_State * L, boost::shared_ptr<Joint> joint);

	bool mod_is_circleshape(lua_State * L, int idx);
	boost::shared_ptr<CircleShape> mod_to_circleshape(lua_State * L, int idx);
	void mod_push_circleshape(lua_State * L, boost::shared_ptr<CircleShape> circleshape);

	bool mod_is_shape(lua_State * L, int idx);
	boost::shared_ptr<Shape> mod_to_shape(lua_State * L, int idx);
	void mod_push_shape(lua_State * L, boost::shared_ptr<Shape> shape);

	bool mod_is_groovejoint(lua_State * L, int idx);
	boost::shared_ptr<GrooveJoint> mod_to_groovejoint(lua_State * L, int idx);
	void mod_push_groovejoint(lua_State * L, boost::shared_ptr<GrooveJoint> groovejoint);

} // love_chipmunk
#endif
