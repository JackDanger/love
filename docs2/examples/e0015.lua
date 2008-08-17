-- Example: Optimizing images

angle = 0

function load()
    image = love.graphics.newImage("images/love-ball.png", love.image_optimize)
end

function update(dt)
    angle = angle + dt
    x, y = 400 + math.cos(angle)*100, 300 + math.sin(angle)*100
end

function draw()
    love.graphics.draw(image, x, y)
end


