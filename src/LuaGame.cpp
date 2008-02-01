#include "LuaGame.h"

#include "using_output.h"
#include "using_filesystem.h"
#include "using_graphics.h"

namespace love
{
	LuaGame::LuaGame(const std::string & source)
	{
		this->source = source;

		// Read config here.
	}

	LuaGame::~LuaGame()
	{
		unload();
	}

	void LuaGame::include(const std::string & filename)
	{
		std::string key = source + filename;

		// If file already is included, return
		if(included.find(key) != included.end())
			return;

		// File is not already included. Include.
		pFile file = filesystem->newFile(source, filename);

		if(!vm.load(file))
		{
			std::stringstream ss;
			ss << "Could not load file: ";
			ss << file->getFilename();
			ss << std::endl;
			error(ss.str());
			return;
		}

		// Mark as included
		included.insert(key);

	}

	bool LuaGame::load()
	{
		// Set up a graphics state.
		graphics->push();
		graphics->setColor(255, 255, 255, 255);
		graphics->setBackgroundColor(0, 0, 0);

		// Open Lua state.
		if(!vm.open())
		{
			error("Could not open Lua state.\n");
			return false;
		}

		// Read mail file.
		pFile main = filesystem->newFile(source, "main.lua");
		if(!vm.load(main))
		{
			error("Could not load main Lua file.\n");
			return false;
		}

		// Check for present functions.
		for(int i =0;i<LOVE_CALLBACK_SIZE;i++) callbacks[i] = false;
		if(vm.isFunction("load")) callbacks[LOVE_CALLBACK_LOAD] = true;
		if(vm.isFunction("update")) callbacks[LOVE_CALLBACK_UPDATE] = true;
		if(vm.isFunction("draw")) callbacks[LOVE_CALLBACK_DRAW] = true;
		if(vm.isFunction("keypressed")) callbacks[LOVE_CALLBACK_KEYPRESSED] = true;
		if(vm.isFunction("keyreleased")) callbacks[LOVE_CALLBACK_KEYRELEASED] = true;
		if(vm.isFunction("mousepressed")) callbacks[LOVE_CALLBACK_MOUSEPRESSED] = true;
		if(vm.isFunction("mousereleased")) callbacks[LOVE_CALLBACK_MOUSERELEASED] = true;
		if(vm.isFunction("event")) callbacks[LOVE_CALLBACK_EVENT] = true;

		// Call load.
		if(callbacks[LOVE_CALLBACK_LOAD])
			vm.call("load");

		return true;
	}

	void LuaGame::unload()
	{
		// Close Lua state.
		vm.close();

		// Clear included files.
		included.clear();

		// Pop graphics state.
		graphics->pop();
	}

	void LuaGame::render()
	{
		if(callbacks[LOVE_CALLBACK_DRAW])
			vm.call("draw");
	}

	void LuaGame::update(float dt)
	{
		if(callbacks[LOVE_CALLBACK_UPDATE])
			vm.calln("update", dt);
	}

	void LuaGame::keyPressed(int key)
	{
		if(callbacks[LOVE_CALLBACK_KEYPRESSED])
			vm.calln("keypressed", (float)key);
	}

	void LuaGame::keyReleased(int key)
	{
		if(callbacks[LOVE_CALLBACK_KEYRELEASED])
			vm.calln("keyreleased", (float)key);
	}

	void LuaGame::mousePressed(float x, float y, int button)
	{
		if(callbacks[LOVE_CALLBACK_MOUSEPRESSED])
			vm.call3n("mousepressed", x, y, (float)button);
	}

	void LuaGame::mouseReleased(float x, float y, int button)
	{
		if(callbacks[LOVE_CALLBACK_MOUSERELEASED])
			vm.call3n("mousereleased", x, y, (float)button);
	}

}// love
