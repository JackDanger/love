-- Example: Loading an Image and displaying it

function load()
    image = love.graphics.newImage("images/love-ball.png")
end

function draw()
    love.graphics.draw(image, 400, 300)
end

