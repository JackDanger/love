--
-- EXF: Example Framework
--
-- This should make examples easier and more enjoyable to use.
-- All examples in one application! Yaay!
--

exf = {}
exf.current = {}
exf.current.id = 0

exf.available = {}

function load()
    
    -- Find available demos.
    exf.available = love.filesystem.enumerate(".")
    exf.font = love.graphics.newFont(love.default_font, 28)
    love.graphics.setFont(exf.font)
    exf.start(53)
end

function update(dt) end
function draw() end
function keypressed(k) end
function keyreleased(k) end
function mousepressed(x, y, b) end
function mousereleased(x, y, b) end

function exf.load()
end

function exf.update(dt)
    if exf.current.update then exf.current.update(dt) end
end

function exf.draw()
    if exf.current.draw then exf.current.draw() end
    
    -- Draw overlay.
    local f = love.graphics.getFont()
    love.graphics.setFont(exf.font)
    love.graphics.drawf("e" .. exf.current.id, love.graphics.getWidth() - 200 - exf.font:getHeight(),
        love.graphics.getHeight() - exf.font:getHeight(), 200, love.align_right)
    love.graphics.setFont(f)
    
end

function exf.keypressed(k)
    if exf.current.keypressed then exf.current.keypressed(k) end
end

function exf.keyreleased(k)
    if exf.current.keyreleased then exf.current.keyreleased(k) end
end

function exf.mousepressed(x, y, b)
    if exf.current.mousepressed then exf.current.mousepressed(x, y, b) end
end

function exf.mousereleased(x, y, b)
    if exf.current.mousereleased then exf.current.mousereleased(x, y, b) end
end

function exf.getn(n)
    local s = ""
    n = tonumber(n)
    local r = n
    if r <= 0 then error("Example IDs must be bigger than 0. (Got: " .. r .. ")") end
    if r >= 10000 then error("Example IDs must be less than 10000. (Got: " .. r .. ")") end
    while r < 1000 do
        s = s .. "0"
        r = r * 10
    end
    s = s .. n
    return s
end

function exf.intable(t, e)
    for k,v in ipairs(t) do
        if v == e then return true end
    end
    return false
end

function exf.start(n)
    local file = "e" .. exf.getn(n) .. ".lua"
    
    if exf.intable(exf.available, file) then
        if not love.filesystem.exists(file) then
           print("Could not load game .. " .. file) 
        else
            love.filesystem.include(file)
        end
        exf.setcallbacks()
        exf.current.id = n
        if exf.current.load then exf.current.load() end
    else
        print("Example ".. exf.getn(n) .. " does not exist.")
    end
end

function exf.setcallbacks()

    -- Create a new current callback set.
    exf.current = {}
    exf.current.id = 0
    
    -- Store the current global callbacks.
    exf.current.load = load
    exf.current.update = update
    exf.current.draw = draw
    exf.current.keypressed = keypressed
    exf.current.keyreleased = keyreleased
    exf.current.mousepressed = mousepressed
    exf.current.mousereleased = mousereleased
    
    -- Reset the current global callbacks.
    load = exf.load
    update = exf.update
    draw = exf.draw
    keypressed = exf.keypressed
    keyreleased = exf.keyreleased
    mousepressed = exf.mousepressed
    mousereleased = exf.mousereleased
    
end
