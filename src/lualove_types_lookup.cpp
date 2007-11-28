#include "lualove_types_lookup.h"

#include "love_script_types.h"
#include "love_types.h"

namespace love
{
	
	static int * lualove_lookup_types;
	
	void lualove_create_lookup()
	{
		lualove_lookup_types = new int[LOVE_NUM_TYPES];
		
		// Add types manually here.
		lualove_lookup_types[LOVE_TYPE_LUA_GAME]				= script_type_p_love__LuaGame;
		//lualove_lookup_types[LOVE_TYPE_IMAGE]					= script_type_p_love__Image;
		//lualove_lookup_types[LOVE_TYPE_POINT]					= script_type_p_love__Point;
		lualove_lookup_types[LOVE_TYPE_KEYBOARD]				= script_type_p_love__Keyboard;
		lualove_lookup_types[LOVE_TYPE_MOUSE]					= script_type_p_love__Mouse;
		lualove_lookup_types[LOVE_TYPE_DISPLAY_MODE]			= script_type_p_love__DisplayMode;
		//lualove_lookup_types[LOVE_TYPE_TEXT]					= script_type_p_love__Text;
		//lualove_lookup_types[LOVE_TYPE_ACTOR]					= script_type_p_love__Actor;
		//lualove_lookup_types[LOVE_TYPE_ACTOR_STATE]				= script_type_p_love__ActorState;
		lualove_lookup_types[LOVE_TYPE_GUI_EVENT]				= script_type_p_love__GUIEvent;
		lualove_lookup_types[LOVE_TYPE_MESSAGE_EVENT]			= script_type_p_love__MessageEvent;
		//lualove_lookup_types[LOVE_TYPE_SCRIPTABLE_ACTOR_STATE]	= script_type_p_love__ScriptableActorState;
		//lualove_lookup_types[LOVE_TYPE_PARTICLE]				= script_type_p_love__Particle;
		//lualove_lookup_types[LOVE_TYPE_PARTICLE_EMITTER]		= script_type_p_love__ParticleEmitter;
	}

	void lualove_clean_lookup()
	{
		delete [] lualove_lookup_types;
	}

	int lualove_get_type(int type)
	{
		// @todo Add type check?
		return lualove_lookup_types[type];
	}

} // love
