#include "NoGame.h"

#include "Filesystem.h"
#include "Module.h"
#include <string>


namespace love
{

	NoGame::NoGame()
	{
	}

	NoGame::~NoGame()
	{
	}

	bool NoGame::load()
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


		// Just pushing Lua-code here, for now. (Should probably be rezhaxed).
		std::string code = 
			" flash = 0 "
			" display = true "
			" function load() "
				" big = love.graphics.newFont(love.default_font, 24) "
				" small = love.graphics.newFont(love.default_font, 12) "
				" love.graphics.setBackgroundColor(0, 138, 255) "
				" moose = love.graphics.newImage(love.default_moose) "
				" logo = love.graphics.newImage(love.default_logo_256) "
			"end"
			" r = 0 "
			" function update(dt) "
				" r = r + dt "
				" flash = flash + dt "
				" if flash > 0.8 then flash = 0; display = not display; end "
			" end "
			" function draw() "
				" love.graphics.setFont(small) "
				" love.graphics.draw(logo, 400, 280) "
				" love.graphics.draw(moose, 400, 380 + math.sin(r)*10) "
				" love.graphics.drawf(\"" LOVE_VERSION_STR "\\n" LOVE_VERSION_CODENAME "\", 480, 560, 300, love.align_right) "
				" love.graphics.setFont(big) "
				" if display then love.graphics.drawf(\"No Game\", 300, 500, 200, love.align_center) end " 
			"end";
		vm.load(code);

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
}
