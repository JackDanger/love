-- Example: Keyboard callbacks

-- Keypressed: Called whenever a key was pressed.
function keypressed(key)
	-- I don't want to register spaces.
	if key ~= love.key_space then
		lastkey = key .. " pressed"
	end
end

-- Keyreleased: Called whenever a key was released.
function keyreleased(key)
	-- I don't want to register spaces.
	if key ~= love.key_space then
		lastkey = key .. " released"
	end
end


-- Load a font and set the text variable.
function load()
	love.graphics.setFont(love.graphics.newFont(love.default_font, 12))
	lastkey = "nothing"
end

-- Output the last mouse button which was pressed/released.
function draw()
	love.graphics.draw("Last key: " .. lastkey, 100, 100)
end
