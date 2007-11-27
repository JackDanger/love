#include "LuaGame.h"

#include "lualove.h"
#include "lualove_globals.h"

#include "AbstractFileSystem.h"
#include "AbstractDisplay.h"
#include "AbstractSoundDevice.h"
#include "GameConfigurationLoader.h"

#include "Core.h"
#include "love.h"

// Temp.
#include "MessageEvent.h"

// Function created by SWIG.
#ifdef __cplusplus
extern "C" 
{
	int extern Love_Init(lua_State * L);
}
#endif


namespace love
{


	LuaGame::LuaGame(const string & source)
	{
		setScript("main");
		setType(LOVE_TYPE_LUA_GAME);

		// Set the source for this game.
		this->source = source;
	}

	LuaGame::~LuaGame()
	{
		delete gfx;
	}

	int LuaGame::init()
	{

		// Load the config for this game.
		config = new GameConfigurationLoader(source);
		config->load();
		
		// Ok. Inited.
		inited = true;
		
		return LOVE_OK;
	}

	int LuaGame::load()
	{
	
		// Init Lua
		L = lua_open();
		luaL_openlibs(L);
		Love_Init(L);
		lualove_init(L); // @todo find out why this cannot init L.
		lualove_push_all_globals(L);
		
		// Important! Change globals points BEFORE main.lua is called.

		// Get a graphics context.
		this->gfx = core->display->getGraphics();

		// Change global values in lualove_globals here.
		game = this;
		graphics = gfx;
		gui = new GUIContainer();
		gui->setDimension(gcn::Rectangle(0, 0, core->display->getCurrentDisplayMode().getWidth(), core->display->getCurrentDisplayMode().getHeight()));
		gui->setOpaque(false);
		core->gui->add(gui);

		// Load entry.lua
		lualove_load(L, core->filesystem->getFile(source, "main.lua"));

		// Check which functions are available.
		lualove_check_functions(L, this, LOVE_METHOD_ALL);

		// Call init
		if(isAvailable(LOVE_METHOD_LOAD))
			lualove_call_load_noarg(L, this);

		return LOVE_OK;
	}

	void LuaGame::unload()
	{

		// End Lua-state
		lua_close(L);
		lualove_close(L);

		// Clear included files.
		included.clear();

		// gui
		//gui->clear();
		core->gui->remove(gui);
		delete gui;

		// Delete graphics context.
		delete gfx;

		loaded = false;
	}

	void LuaGame::render()
	{
		gfx->clear();

		if(isAvailable(LOVE_METHOD_RENDER))
			lualove_call_render_noarg(L, this);
	}

	void LuaGame::update(float dt)
	{
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update_noarg(L, this, dt);
	}

	void LuaGame::suspend()
	{
		// Stop all playing audio
		core->audio->stop();
	}

	void LuaGame::resume()
	{
		Game::resume();
	}

	void LuaGame::reloadGraphics()
	{
		// Reload thumbnail.
		config->getThumb()->reload();
	}

	void LuaGame::keyPressed(int key)
	{
		if(isAvailable(LOVE_METHOD_KEYPRESSED))
			lualove_call_keypressed_noarg(L, this, key);
	}

	void LuaGame::keyReleased(int key)
	{
		if(isAvailable(LOVE_METHOD_KEYRELEASED))
			lualove_call_keyreleased_noarg(L, this, key);
	}

	void LuaGame::mousePressed(float x, float y, int button)
	{
		
		// Fire a message event.
		if(isAvailable(LOVE_METHOD_MOUSEPRESSED))
			lualove_call_mousepressed_noarg(L, this, x, y, button);
	}

	void LuaGame::mouseReleased(float x, float y, int button)
	{
		if(isAvailable(LOVE_METHOD_MOUSERELEASED))
			lualove_call_mousereleased_noarg(L, this, x, y, button);
	}

	void LuaGame::eventFired(pEvent e)
	{
		//pMessageEvent pme = dynamic_pointer_cast<MessageEvent, Event>(e);

		//printf("Event: %s\n", pme->getMessage().c_str());

		// Must pass this on to Lua, like this:
		// luaPushPointer(L, (void*)e.get(), script_types_lookup[e.getType()], 0);
		// global_script->eventFired(L, (void*)e.get(), e.getType());




		// Convert generic event to specific event.

		switch(e->getType())
		{
			case LOVE_TYPE_GUI_EVENT:
			case LOVE_TYPE_MESSAGE_EVENT:

				if(isAvailable(LOVE_METHOD_EVENT))
					lualove_call_event(L, this, (void*)e.get(), e->getType()); 

				break;
			
			// We might not want to pass ALL events to Lua.
		}

	}

	void LuaGame::include(const char * filename)
	{
		string key = source + string(filename);

		// If file already is included, return
		if(included.find(key) != included.end())
			return;

		// File is not already included. Include.
		//lualove_load(L, key);
		lualove_load(L, core->filesystem->getFile(source, string(filename)));

		// Mark as included
		included.insert(key);

	}

}// love
