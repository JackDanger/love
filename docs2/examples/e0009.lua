-- Example: Timing code

function load()
    -- Get time before the code to be timed.
    t_start = love.timer.getTime()
    
    -- Load 20 fonts.
    for i=12,32 do
        local f = love.graphics.newFont(love.default_font, i)
        love.graphics.setFont(f)
    end
    
    -- Get time after.
    t_end = love.timer.getTime()
    
end

function draw()
    love.graphics.draw("Spent " .. (t_end-t_start) .. " seconds.", 50, 50)
end
