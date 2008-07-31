-- Example: Getting the x- and y-position of the mouse

function load()
    local f = love.graphics.newFont(love.default_font, 14)
    love.graphics.setFont(f)
end

function draw()
    -- Gets the x- and y-position of the mouse.
    local x = love.mouse.getX()
    local y = love.mouse.getY()
    -- Draws the position on screen.
    love.graphics.draw("The mouse is at (" .. x .. "," .. y .. ")", 50, 50)
end
