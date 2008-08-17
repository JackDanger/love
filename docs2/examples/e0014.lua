-- Example: Moving stuff with the keyboard

x, y = 400, 300

function load()
    image = love.graphics.newImage("images/love-ball.png")
end

function update(dt)
    if love.keyboard.isDown(love.key_left) then
	x = x - 100 * dt
    end
    if love.keyboard.isDown(love.key_right) then
	x = x + 100 * dt
    end
    if love.keyboard.isDown(love.key_up) then
	y = y - 100 * dt
    end
    if love.keyboard.isDown(love.key_down) then
	y = y + 100 * dt
    end
end

function draw()
    love.graphics.draw(image, x, y)
end


