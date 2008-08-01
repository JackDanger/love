-- Example: FPS and delta-time

function load()
    local f = love.graphics.newFont(love.default_font, 12)
    love.graphics.setFont(f)
end

function draw()
    -- Draw the current FPS.
    love.graphics.draw("FPS: " .. love.timer.getFPS(), 50, 50)
    -- Draw the current delta-time. (The same value
    -- is passed to update each frame).
    love.graphics.draw("dt: " .. love.timer.getDelta(), 50, 100)
end
