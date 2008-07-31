-- Example: Checking for pressed mouse buttons

function load()
    local f = love.graphics.newFont(love.default_font, 14)
    love.graphics.setFont(f)
end

function draw()
    -- Left mouse button.
    if love.mouse.isDown(love.mouse_left) then
        love.graphics.draw("Left mouse button is down", 50, 50)
    end
    -- Right mouse button.
    if love.mouse.isDown(love.mouse_right) then
        love.graphics.draw("Right mouse button is down", 50, 100)
    end   
end