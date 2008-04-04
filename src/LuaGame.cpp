#include "LuaGame.h"

#include "Filesystem.h"
#include "Module.h"

namespace love
{

	LuaGame::LuaGame()
	{
	}

	LuaGame::~LuaGame()
	{
	}

	bool LuaGame::require(Module & m)
	{
		libs.push_back(m.getLuaOpen());
		return true;
	}

	bool LuaGame::load()
	{
		// Open Lua VM and standard libraries.
		if(!vm.open())
		{
			return false;
		}
		
		// Open LÖVE-libraries.
		for(int i = 0; i < (int)libs.size(); i++)
		{
			// Get the library function pointer.
			fptr_luaopen lib = libs[i];

			// Open the library.
			lib(vm.getL());
		}

		// Check that filesystem is set.
		if( filesystem == 0)
		{
			printf("No filesystem is set in game\n");
			return false;
		}

		// By now the filesystem should be mounted, and there should
		// be one file called main.lua.
		if(filesystem->exists("main.lua"))
		{
			pFile main(new File("main.lua"));
			if(!filesystem->load(main))
			{
				printf("Could not load main Lua file.\n");
				return false;
			}

			// Parse the main file.
			if(!vm.load(main))
			{
				printf("Could not parse the main.lua\n");
				return false;
			}

		}

		// Check for present functions.
		for(int i =0;i<CALLBACK_SIZE;i++) callbacks[i] = false;
		if(vm.isFunction("load")) callbacks[CALLBACK_LOAD] = true;
		if(vm.isFunction("update")) callbacks[CALLBACK_UPDATE] = true;
		if(vm.isFunction("draw")) callbacks[CALLBACK_DRAW] = true;
		if(vm.isFunction("keypressed")) callbacks[CALLBACK_KEYPRESSED] = true;
		if(vm.isFunction("keyreleased")) callbacks[CALLBACK_KEYRELEASED] = true;
		if(vm.isFunction("mousepressed")) callbacks[CALLBACK_MOUSEPRESSED] = true;
		if(vm.isFunction("mousereleased")) callbacks[CALLBACK_MOUSERELEASED] = true;
		if(vm.isFunction("event")) callbacks[CALLBACK_EVENT] = true;

		// Call load.
		if(callbacks[CALLBACK_LOAD])
			vm.call("load");

		return true;
	}

	bool LuaGame::unload()
	{
		// Close the virtual machine.
		vm.close();
		return true;
	}

	void LuaGame::update(float dt)
	{
		if(callbacks[CALLBACK_UPDATE])
			vm.calln("update", dt);
	}

	void LuaGame::draw()
	{
		if(callbacks[CALLBACK_DRAW])
			vm.call("draw");
	}

	void LuaGame::keyPressed(int key)
	{
		if(callbacks[CALLBACK_KEYPRESSED])
			vm.calln("keypressed", (float)key);
	}

	void LuaGame::keyReleased(int key)
	{
		if(callbacks[CALLBACK_KEYRELEASED])
			vm.calln("keyreleased", (float)key);
	}

	void LuaGame::mousePressed(int x, int y, int button)
	{
		if(callbacks[CALLBACK_MOUSEPRESSED])
			vm.call3n("mousepressed", (float)x, (float)y, (float)button);
	}

	void LuaGame::mouseReleased(int x, int y, int button)
	{
		if(callbacks[CALLBACK_MOUSERELEASED])
			vm.call3n("mousereleased", (float)x, (float)y, (float)button);
	}

	void LuaGame::mouseMoved(int xrel, int yrel)
	{
		//if(callbacks[CALLBACK_MOUSEMOVED])
		//	vm.call3n("mousemoved", (float)xrel, (float)yrel);
	}
}
