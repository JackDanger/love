-- Example: Cursor Visibility

function load()
    -- Hide mouse on startup.
    love.mouse.setVisible(false)
    
    local f = love.graphics.newFont(love.default_font, 12)
    love.graphics.setFont(f)
end

-- Toggle cursor visibility.
function keypressed(k)
    if k == love.key_v then
	if love.mouse.isVisible() then
	    love.mouse.setVisible(false)
	else
	    love.mouse.setVisible(true)
	end
    end
end

function draw()
    love.graphics.draw("Press V to toggle visibility.", 50, 50)
end