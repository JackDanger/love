-- Example: Filler

angle = 0

function load()
    image = love.graphics.newImage("images/love-ball.png", love.image_optimize)
end

function update(dt)
    angle = angle + dt
    x, y = 400 + math.cos(angle)*100, 300 + math.sin(angle)*100
end

function draw()
    local rot = angle*180/math.pi
    local sx = math.cos(angle)*3
    local sy = math.sin(angle)*2
    love.graphics.draw(image, x, y, rot, sx, sy)
end
