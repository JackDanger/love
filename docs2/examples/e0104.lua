-- Example: Dispay modes
-- Author: surtic

function load()

	-- Get the display modes.
   modes = love.graphics.getModes()
   
	-- The table looks like this:
	-- modes = {
	--	  { width = 800, height = 600 },
	--	  { width = 1024, height = 768 },
	-- }

   local font = love.graphics.newFont(love.default_font)
   love.graphics.setFont(font)
end

function draw()
	love.graphics.draw("Supported modes: ", 50, 50)
   for i, mode in ipairs(modes) do
      local desc = string.format("mode %d: %dx%d", i, mode.width, mode.height)
      love.graphics.draw(desc, 50, 50 + i * 20)
   end
end
