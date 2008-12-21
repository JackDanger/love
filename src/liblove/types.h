/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-30
**/

#ifndef LOVE_TYPES_H
#define LOVE_TYPES_H

// STD
#include <bitset>

namespace love
{
	enum
	{
		// Cross-module types.
		LOVE_OBJECT_ID = 0,
		LOVE_FILE_ID, 
		LOVE_DRAWABLE_ID,
		LOVE_DATA_ID,

		// Module specific types.

		// Graphics
		LOVE_IMAGE_ID,
		LOVE_ANIMATION_ID,
		LOVE_COLOR_ID,
		LOVE_FONT_ID,
		LOVE_PARTICLE_SYSTEM_ID,

		// Image
		LOVE_IMAGE_DATA_ID,

		// Audio
		LOVE_AUDIBLE_ID,
		LOVE_SOUND_ID,
		LOVE_MUSIC_ID,

		// Sound
		LOVE_SOUND_DATA_ID,

		// Physics
		LOVE_WORLD_ID,
		LOVE_CONTACT_ID,
		LOVE_BODY_ID,
		LOVE_SHAPE_ID,
		LOVE_CIRCLE_SHAPE_ID,
		LOVE_POLYGON_SHAPE_ID,
		LOVE_JOINT_ID,
		LOVE_MOUSE_JOINT_ID,
		LOVE_DISTANCE_JOINT_ID,
		LOVE_PRISMATIC_JOINT_ID,
		LOVE_REVOLUTE_JOINT_ID,

		// Modules.
		LOVE_PHYSFS_ID, 
		LOVE_OPENGL_ID, 
		LOVE_DIRECT3D_ID,
		LOVE_BOX2D_ID,
		LOVE_DEVIL_ID,
		LOVE_SDLSOUND_ID,
		LOVE_OPENAL_ID,

		// Count the number of bits needed.
		LOVE_BIT_SIZE
	};

	typedef std::bitset<LOVE_BIT_SIZE> bits;

	static const bits LOVE_OBJECT_BITS = bits(1) << LOVE_OBJECT_ID;
	static const bits LOVE_FILE_BITS = (bits(1) << LOVE_FILE_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_DRAWABLE_BITS = (bits(1) << LOVE_DRAWABLE_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_DATA_BITS = (bits(1) << LOVE_DATA_ID) | LOVE_OBJECT_BITS;

	// Graphics.
	static const bits LOVE_IMAGE_BITS = (bits(1) << LOVE_IMAGE_ID) | LOVE_DRAWABLE_BITS;
	static const bits LOVE_ANIMATION_BITS = (bits(1) << LOVE_ANIMATION_ID) | LOVE_DRAWABLE_BITS;
	static const bits LOVE_COLOR_BITS = (bits(1) << LOVE_COLOR_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_FONT_BITS = (bits(1) << LOVE_FONT_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_PARTICLE_SYSTEM_BITS = (bits(1) << LOVE_PARTICLE_SYSTEM_ID) | LOVE_DRAWABLE_BITS;

	// Image.
	static const bits LOVE_IMAGE_DATA_BITS = (bits(1) << LOVE_IMAGE_DATA_ID) | LOVE_DATA_BITS;
	
	// Audio.
	static const bits LOVE_AUDIBLE_BITS = (bits(1) << LOVE_AUDIBLE_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_SOUND_BITS = (bits(1) << LOVE_SOUND_ID) | LOVE_AUDIBLE_BITS;
	static const bits LOVE_MUSIC_BITS = (bits(1) << LOVE_MUSIC_ID) | LOVE_AUDIBLE_BITS;

	// Sound.
	static const bits LOVE_SOUND_DATA_BITS = (bits(1) << LOVE_SOUND_DATA_ID) | LOVE_DATA_BITS;

	// Physics.
	static const bits LOVE_WORLD_BITS = (bits(1) << LOVE_WORLD_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_CONTACT_BITS = (bits(1) << LOVE_CONTACT_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_BODY_BITS = (bits(1) << LOVE_BODY_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_SHAPE_BITS = (bits(1) << LOVE_SHAPE_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_CIRCLE_SHAPE_BITS = (bits(1) << LOVE_CIRCLE_SHAPE_ID) | LOVE_SHAPE_BITS;
	static const bits LOVE_POLYGON_SHAPE_BITS = (bits(1) << LOVE_POLYGON_SHAPE_ID) | LOVE_SHAPE_BITS;
	static const bits LOVE_JOINT_BITS = (bits(1) << LOVE_JOINT_ID) | LOVE_OBJECT_BITS;
	static const bits LOVE_MOUSE_JOINT_BITS = (bits(1) << LOVE_MOUSE_JOINT_ID) | LOVE_JOINT_BITS;
	static const bits LOVE_DISTANCE_JOINT_BITS = (bits(1) << LOVE_DISTANCE_JOINT_ID) | LOVE_JOINT_BITS;
	static const bits LOVE_PRISMATIC_JOINT_BITS = (bits(1) << LOVE_PRISMATIC_JOINT_ID) | LOVE_JOINT_BITS;
	static const bits LOVE_REVOLUTE_JOINT_BITS = (bits(1) << LOVE_REVOLUTE_JOINT_ID) | LOVE_JOINT_BITS;

	// Modules.
	static const bits LOVE_PHYSFS_BITS = bits(1) << LOVE_PHYSFS_ID;
	static const bits LOVE_OPENGL_BITS = bits(1) << LOVE_OPENGL_ID;
	static const bits LOVE_DIRECT3D_BITS = bits(1) << LOVE_DIRECT3D_ID;
	static const bits LOVE_BOX2D_BITS = bits(1) << LOVE_BOX2D_ID;
	static const bits LOVE_DEVIL_BITS = bits(1) << LOVE_DEVIL_ID;
	static const bits LOVE_SDLSOUND_BITS = bits(1) << LOVE_SDLSOUND_ID;
	static const bits LOVE_OPENAL_BITS = bits(1) << LOVE_OPENAL_ID;

	// Wraps all userdata pointers.
	struct userdata
	{
		bits flags; // Holds type information.
		void * data;
		bool own; // True if Lua should delete on GC.
	};

} // love

#endif // LOVE_TYPES_H
