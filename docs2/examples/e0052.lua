-- Example: Mouse callbacks

-- Mousepressed: Called whenever a mouse button was pressed,
-- passing the button and the x and y coordiante it was pressed at.
function mousepressed(x, y, button)
	-- Checks which button was pressed.
	if button == love.mouse_left then
		last = "left pressed"
	elseif button == love.mouse_right then
		last = "right pressed"
	elseif button == love.mouse_middle then
		last = "middle pressed"
	elseif button == love.mouse_wheelup then
		-- Won't show up because scrollwheels are instantly "released",
		-- but the event is legitimate.
		last = "scrollwheel up pressed"
	elseif button == love.mouse_wheeldown then
		-- Won't show up because scrollwheels are instantly "released",
		-- but the event is legitimate.
		last = "scrollwheel down pressed"
	end
	
	last = last .. " @ (" .. x .. "x" .. y .. ")"
end

-- Mousereleased: Called whenever a mouse button was released,
-- passing the button and the x and y coordiante it was released at.
function mousereleased(x, y, button)
	-- Checks which button was released.
	if button == love.mouse_left then
		last = "left released"
	elseif button == love.mouse_right then
		last = "right released"
	elseif button == love.mouse_middle then
		last = "middle released"
	elseif button == love.mouse_wheelup then
		last = "scrollwheel up released"
	elseif button == love.mouse_wheeldown then
		last = "scrollwheel down released"
	end
	
	last = last .. " @ (" .. x .. "x" .. y .. ")"
end


-- Load a font and set the text variable.
function load()
	love.graphics.setFont(love.graphics.newFont(love.default_font, 12))
	last = "nothing"
end

-- Output the last mouse button which was pressed/released.
function draw()
	love.graphics.draw("Last mouse click: " .. last, 100, 100)
end
