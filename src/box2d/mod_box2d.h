/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This file was AUTOGENERATED by swigfusion! Please
* do not edit this file manually.
* 
* @author Anders Ruud / swigfusion
* @date 2008-09-25
**/

#ifndef LOVE_MOD_FUSION_BOX2D_H
#define LOVE_MOD_FUSION_BOX2D_H

// Boost
#include <boost/shared_ptr.hpp>


// Function from SWIG which opens the module.
extern "C" {
    int luaopen_mod_box2d(lua_State * L);
}

// Types found:
// PolygonShape (SWIGTYPE_p_boost__shared_ptrT_love_box2d__PolygonShape_t)
// Shape (SWIGTYPE_p_boost__shared_ptrT_love_box2d__Shape_t)
// Body (SWIGTYPE_p_boost__shared_ptrT_love_box2d__Body_t)
// CircleShape (SWIGTYPE_p_boost__shared_ptrT_love_box2d__CircleShape_t)
// PrismaticJoint (SWIGTYPE_p_boost__shared_ptrT_love_box2d__PrismaticJoint_t)
// RevoluteJoint (SWIGTYPE_p_boost__shared_ptrT_love_box2d__RevoluteJoint_t)
// MouseJoint (SWIGTYPE_p_boost__shared_ptrT_love_box2d__MouseJoint_t)
// Joint (SWIGTYPE_p_boost__shared_ptrT_love_box2d__Joint_t)
// Contact (SWIGTYPE_p_boost__shared_ptrT_love_box2d__Contact_t)
// DistanceJoint (SWIGTYPE_p_boost__shared_ptrT_love_box2d__DistanceJoint_t)
// World (SWIGTYPE_p_boost__shared_ptrT_love_box2d__World_t)

// Fused: 
// World::getGravity => _wrap_method_World_getGravity
// World::getCallback => _wrap_method_World_getCallback
// World::setCallback => _wrap_method_World_setCallback
// Body::getLocalPoint => _wrap_method_Body_getLocalPoint
// Body::getLocalCenter => _wrap_method_Body_getLocalCenter
// Body::getWorldPoint => _wrap_method_Body_getWorldPoint
// Body::getLocalVector => _wrap_method_Body_getLocalVector
// Body::getVelocityLocalPoint => _wrap_method_Body_getVelocityLocalPoint
// Body::getVelocityWorldPoint => _wrap_method_Body_getVelocityWorldPoint
// Body::getPosition => _wrap_method_Body_getPosition
// Body::getVelocity => _wrap_method_Body_getVelocity
// Body::getWorldVector => _wrap_method_Body_getWorldVector
// Body::getWorldCenter => _wrap_method_Body_getWorldCenter
// Body::int _wrap_method_Body_destroy(lua_State * L) => _wrap_method_Body_destroy
// CircleShape::getCategory => _wrap_method_CircleShape_getCategory
// CircleShape::getData => _wrap_method_CircleShape_getData
// CircleShape::testSegment => _wrap_method_CircleShape_testSegment
// CircleShape::getBoundingBox => _wrap_method_CircleShape_getBoundingBox
// CircleShape::setCategory => _wrap_method_CircleShape_setCategory
// CircleShape::setData => _wrap_method_CircleShape_setData
// CircleShape::getMask => _wrap_method_CircleShape_getMask
// CircleShape::setMask => _wrap_method_CircleShape_setMask
// CircleShape::int _wrap_method_CircleShape_destroy(lua_State * L) => _wrap_method_CircleShape_destroy
// PolygonShape::getData => _wrap_method_PolygonShape_getData
// PolygonShape::setCategory => _wrap_method_PolygonShape_setCategory
// PolygonShape::getBoundingBox => _wrap_method_PolygonShape_getBoundingBox
// PolygonShape::getCategory => _wrap_method_PolygonShape_getCategory
// PolygonShape::getPoints => _wrap_method_PolygonShape_getPoints
// PolygonShape::testSegment => _wrap_method_PolygonShape_testSegment
// PolygonShape::setData => _wrap_method_PolygonShape_setData
// PolygonShape::getMask => _wrap_method_PolygonShape_getMask
// PolygonShape::setMask => _wrap_method_PolygonShape_setMask
// PolygonShape::int _wrap_method_PolygonShape_destroy(lua_State * L) => _wrap_method_PolygonShape_destroy
// Contact::getPosition => _wrap_method_Contact_getPosition
// Contact::getVelocity => _wrap_method_Contact_getVelocity
// Contact::getNormal => _wrap_method_Contact_getNormal
// DistanceJoint::getReactionForce => _wrap_method_DistanceJoint_getReactionForce
// DistanceJoint::getAnchors => _wrap_method_DistanceJoint_getAnchors
// DistanceJoint::int _wrap_method_DistanceJoint_destroy(lua_State * L) => _wrap_method_DistanceJoint_destroy
// MouseJoint::getReactionForce => _wrap_method_MouseJoint_getReactionForce
// MouseJoint::getTarget => _wrap_method_MouseJoint_getTarget
// MouseJoint::getAnchors => _wrap_method_MouseJoint_getAnchors
// MouseJoint::int _wrap_method_MouseJoint_destroy(lua_State * L) => _wrap_method_MouseJoint_destroy
// RevoluteJoint::getLimits => _wrap_method_RevoluteJoint_getLimits
// RevoluteJoint::getReactionForce => _wrap_method_RevoluteJoint_getReactionForce
// RevoluteJoint::getAnchors => _wrap_method_RevoluteJoint_getAnchors
// RevoluteJoint::int _wrap_method_RevoluteJoint_destroy(lua_State * L) => _wrap_method_RevoluteJoint_destroy
// PrismaticJoint::getLimits => _wrap_method_PrismaticJoint_getLimits
// PrismaticJoint::getReactionForce => _wrap_method_PrismaticJoint_getReactionForce
// PrismaticJoint::getAnchors => _wrap_method_PrismaticJoint_getAnchors
// PrismaticJoint::int _wrap_method_PrismaticJoint_destroy(lua_State * L) => _wrap_method_PrismaticJoint_destroy

namespace love_box2d
{

	//Forward declarations.
	class PolygonShape;
	class Shape;
	class Body;
	class CircleShape;
	class PrismaticJoint;
	class RevoluteJoint;
	class MouseJoint;
	class Joint;
	class Contact;
	class DistanceJoint;
	class World;

	bool mod_is_polygonshape(lua_State * L, int idx);
	boost::shared_ptr<PolygonShape> mod_to_polygonshape(lua_State * L, int idx);
	void mod_push_polygonshape(lua_State * L, boost::shared_ptr<PolygonShape> polygonshape);

	bool mod_is_shape(lua_State * L, int idx);
	boost::shared_ptr<Shape> mod_to_shape(lua_State * L, int idx);
	void mod_push_shape(lua_State * L, boost::shared_ptr<Shape> shape);

	bool mod_is_body(lua_State * L, int idx);
	boost::shared_ptr<Body> mod_to_body(lua_State * L, int idx);
	void mod_push_body(lua_State * L, boost::shared_ptr<Body> body);

	bool mod_is_circleshape(lua_State * L, int idx);
	boost::shared_ptr<CircleShape> mod_to_circleshape(lua_State * L, int idx);
	void mod_push_circleshape(lua_State * L, boost::shared_ptr<CircleShape> circleshape);

	bool mod_is_prismaticjoint(lua_State * L, int idx);
	boost::shared_ptr<PrismaticJoint> mod_to_prismaticjoint(lua_State * L, int idx);
	void mod_push_prismaticjoint(lua_State * L, boost::shared_ptr<PrismaticJoint> prismaticjoint);

	bool mod_is_revolutejoint(lua_State * L, int idx);
	boost::shared_ptr<RevoluteJoint> mod_to_revolutejoint(lua_State * L, int idx);
	void mod_push_revolutejoint(lua_State * L, boost::shared_ptr<RevoluteJoint> revolutejoint);

	bool mod_is_mousejoint(lua_State * L, int idx);
	boost::shared_ptr<MouseJoint> mod_to_mousejoint(lua_State * L, int idx);
	void mod_push_mousejoint(lua_State * L, boost::shared_ptr<MouseJoint> mousejoint);

	bool mod_is_joint(lua_State * L, int idx);
	boost::shared_ptr<Joint> mod_to_joint(lua_State * L, int idx);
	void mod_push_joint(lua_State * L, boost::shared_ptr<Joint> joint);

	bool mod_is_contact(lua_State * L, int idx);
	boost::shared_ptr<Contact> mod_to_contact(lua_State * L, int idx);
	void mod_push_contact(lua_State * L, boost::shared_ptr<Contact> contact);

	bool mod_is_distancejoint(lua_State * L, int idx);
	boost::shared_ptr<DistanceJoint> mod_to_distancejoint(lua_State * L, int idx);
	void mod_push_distancejoint(lua_State * L, boost::shared_ptr<DistanceJoint> distancejoint);

	bool mod_is_world(lua_State * L, int idx);
	boost::shared_ptr<World> mod_to_world(lua_State * L, int idx);
	void mod_push_world(lua_State * L, boost::shared_ptr<World> world);

} // love_box2d

#endif
