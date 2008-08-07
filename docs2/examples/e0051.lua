-- Example: Basic callbacks

elapsed = 0

-- Load: called when the game
-- loads.
function load()
    -- Load a font
    local f = love.graphics.newFont(love.default_font, 12)
    love.graphics.setFont(f)
end

-- Update: Called each frame. Update the
-- state of your game here.
function update(dt)
    elapsed = elapsed + dt
end

-- Draw: Called each frame. The game
-- should be drawn in this functions.
function draw()
    love.graphics.draw("Elapsed time: " .. elapsed)
end

