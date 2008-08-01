-- Example: Checking if a key is down

function draw()
    -- Checks whether the return key is down or not.
    if love.keyboard.isDown(love.key_return) then
        love.graphics.draw("The key is down.", 50, 50)
    else
        love.graphics.draw("The key isn't down.", 50, 50)
    end
end
