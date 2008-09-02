--
-- EXF: Example Framework
--
-- This should make examples easier and more enjoyable to use.
-- All examples in one application! Yaay!
--

exf = {}
exf.current = nil

exf.available = {}

function load()
    
    exf.list = List:new()
    exf.smallfont = love.graphics.newFont(love.default_font, 12)
    exf.bigfont = love.graphics.newFont(love.default_font, 24)
    exf.list.font = exf.smallfont

    exf.bigball = love.graphics.newImage("images/love-big-ball.png")
    
    -- Find available demos.
    local files = love.filesystem.enumerate("")
    
    for i,v in ipairs(files) do
	local unused1, unused2, n = string.find(v, "e(%d%d%d%d)%.lua")
	if n then
	    table.insert(exf.available, v);
	    local file = love.filesystem.newFile(v, love.file_read)
	    love.filesystem.open(file)
	    local contents = love.filesystem.read(file, 100)
	    local s, e, c = string.find(contents, "Example: ([%a%p ]-)[\r\n]")
	    love.filesystem.close(file)
	    if not c then c = "Untitled" end
	    local title = exf.getn(n) .. " " .. c
	    exf.list:add(title)
	end
    end
    
    exf.list:done()  
    exf.resume()
end

function update(dt) end
function draw() end
function keypressed(k) end
function keyreleased(k) end
function mousepressed(x, y, b) end
function mousereleased(x, y, b) end

function exf.empty() end

function exf.update(dt)
    exf.list:update(dt)
end

function exf.draw()    
    love.graphics.setBackgroundColor(54, 172, 248)
    
    love.graphics.setColor(255, 255, 255)
    love.graphics.setFont(exf.bigfont)
    love.graphics.draw("Example Browser", 50, 50)
    love.graphics.draw("Usage", 500, 50)
    
    love.graphics.setFont(exf.smallfont)
    love.graphics.draw("Browse and click on the example you \nwant to run. To return the the example \nselection screen, press escape.\n\nIf you would like to add an \nexample, please contact us! ^.^)/", 500, 80)
    
    
    
    love.graphics.draw(exf.bigball, 800 - 64, 600 - 64)
    
    exf.list:draw()
end

function exf.keypressed(k)
end

function exf.keyreleased(k)
end

function exf.mousepressed(x, y, b)
    exf.list:mousepressed(x, y, b)
end

function exf.mousereleased(x, y, b)
    exf.list:mousereleased(x, y, b)
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

function exf.start(item)
    local e_id = string.sub(item, 1, 4)
    local e_rest = string.sub(item, 5)
    local file = "e" .. e_id .. ".lua"
    
    if exf.intable(exf.available, file) then
        if not love.filesystem.exists(file) then
           print("Could not load game .. " .. file) 
        else
	
	    -- Clear all callbacks.
	    load = exf.empty
	    update = exf.empty
	    draw = exf.empty
	    keypressed = exf.empty
	    keyreleased = exf.empty
	    mousepressed = exf.empty
	    mousereleased = exf.empty
    
            love.filesystem.include(file)	
	    exf.clear()
	    
	    love.graphics.setCaption(e_rest)
	    
	    -- Redirect keypress
	    local o_keypressed = keypressed
	    keypressed =
		function(k)
		    if k == love.key_escape then
			exf.resume()
		    end
		    o_keypressed(k)
		end
	    
	    load()   
        end
    else
        print("Example ".. e_id .. " does not exist.")
    end
end

function exf.clear()
    love.graphics.setBackgroundColor(0,0,0)
    love.graphics.setColor(255, 255, 255)
    love.graphics.setLine(1, love.line_smooth)
    love.graphics.setColorMode(love.color_normal)
    love.graphics.setBlendMode(love.blend_normal)
    love.mouse.setVisible(true)
end	

function exf.resume()
    load = nil
    update = exf.update
    draw = exf.draw
    keypressed = exf.keypressed
    keyreleased = exf.keyreleased
    mousepressed = exf.mousepressed
    mousereleased = exf.mousereleased
    
    love.mouse.setVisible(true)
    love.graphics.setCaption("LOVE Example Browser")
    
end

function inside(mx, my, x, y, w, h)
    return mx >= x and mx <= (x+w) and my >= y and my <= (y+h)
end


----------------------
-- List object
----------------------

List = {}

function List:new()
    o = {}
    setmetatable(o, self)
    self.__index = self
    
    o.items = {}
    
    o.x = 50
    o.y = 70
    
    o.width = 400
    o.height = 500
    
    o.item_height = 23
    o.sum_item_height = 0
    
    o.bar_size = 20
    o.bar_pos = 0
    o.bar_max_pos = 0
    o.bar_width = 15
    o.bar_lock = nil
    
    return o
end

function List:add(item)
    table.insert(self.items, item)
end

function List:done()
    
    self.items.n = #self.items

    -- Recalc bar size.
    self.bar_pos = 0
    
    local num_items = (self.height/self.item_height)
    local ratio = num_items/self.items.n
    self.bar_size = self.height * ratio
    self.bar_max_pos = self.height - self.bar_size - 3
    
    -- Calculate height of everything.
    self.sum_item_height = (self.item_height+1) * self.items.n + 2
    
end

function List:hasBar()
    return self.sum_item_height > self.height
end

function List:getBarRatio()
    return self.bar_pos/self.bar_max_pos
end

function List:getOffset()
    local ratio = self.bar_pos/self.bar_max_pos
    return math.floor((self.sum_item_height-self.height)*ratio + 0.5)
end

function List:update(dt)
    if self.bar_lock then
	local dy = math.floor(love.mouse.getY()-self.bar_lock.y+0.5)	
	self.bar_pos = self.bar_pos + dy
	
	if self.bar_pos < 0 then
	    self.bar_pos = 0
	elseif self.bar_pos > self.bar_max_pos then
	   self.bar_pos = self.bar_max_pos
	end
	
	self.bar_lock.y = love.mouse.getY()
	
    end
end

function List:mousepressed(mx, my, b)
    if self:hasBar() then
	if b == love.mouse_left then
	    local x, y, w, h = self:getBarRect()
	    if inside(mx, my, x, y, w, h) then
		self.bar_lock = { x = mx, y = my }
	    end
	end
	  
	local per_pixel = (self.sum_item_height-self.height)/self.bar_max_pos
	local bar_pixel_dt = math.floor(((self.item_height)*3)/per_pixel + 0.5)
	
	if b == love.mouse_wheeldown then
	    self.bar_pos = self.bar_pos + bar_pixel_dt
	    if self.bar_pos > self.bar_max_pos then self.bar_pos = self.bar_max_pos end
	elseif b == love.mouse_wheelup then
	    self.bar_pos = self.bar_pos - bar_pixel_dt
	    if self.bar_pos < 0 then self.bar_pos = 0 end
	end
    end
    
    if b == love.mouse_left and inside(mx, my, self.x+2, self.y+1, self.width-3, self.height-3) then
	local tx, ty = mx-self.x, my + self:getOffset() - self.y
	local index = math.floor((ty/self.sum_item_height)*self.items.n)
	local f = self.items[index+1]
	if f then
	    exf.start(f)
	end
    end    
end

function List:mousereleased(x, y, b)
    if self:hasBar() then
	if b == love.mouse_left then
	    self.bar_lock = nil
	end
    end
end

function List:getBarRect()
    return
	self.x+self.width+2, self.y+1+self.bar_pos,
	self.bar_width-3, self.bar_size    
end

function List:getItemRect(i)
	return
	    self.x+2, self.y+((self.item_height+1)*(i-1)+1)-self:getOffset(),
	    self.width-3, self.item_height    
end

function List:draw()
    love.graphics.setLine(1, love.line_rough)
    love.graphics.setFont(self.font)
    
    love.graphics.setColor(48, 156, 225)
    
    local mx, my = love.mouse.getPosition()
    
    -- Get interval to display.
    local start_i = math.floor( self:getOffset()/(self.item_height+1) ) + 1
    local end_i = start_i+math.floor( self.height/(self.item_height+1) ) + 1
    if end_i > self.items.n then end_i = self.items.n end
    
    
    love.graphics.setScissor(self.x, self.y, self.width, self.height)
    
    -- Items.
    for i = start_i,end_i do
	
	local x, y, w, h = self:getItemRect(i)
	local hover = inside(mx, my, x, y, w, h)
	
	if hover then
	    love.graphics.setColor(72, 131, 168)
	else
	    love.graphics.setColor(48, 156, 225)
	end
	
	love.graphics.rectangle(love.draw_fill, x, y, w, h)
    
	if hover then
	    love.graphics.setColor(255, 255, 255)
	else
	    love.graphics.setColor(197, 232, 255)
	end
	
	local e_id = string.sub(self.items[i], 1, 5)
	local e_rest = string.sub(self.items[i], 5)
	
	love.graphics.draw(e_id, x+10, y+16)
	love.graphics.draw(e_rest, x+50, y+16)
    
    end
    
    love.graphics.setScissor()
    
    -- Bar.
    if self:hasBar() then
	local x, y, w, h = self:getBarRect()
	local hover = inside(mx, my, x, y, w, h)
	
	if hover or self.bar_lock then
	    love.graphics.setColor(72, 131, 168)
	else
	    love.graphics.setColor(48, 156, 225)
	end
	love.graphics.rectangle(love.draw_fill, x, y, w, h)
    end
    
    -- Border.
    love.graphics.setColor(72, 131, 168)
    love.graphics.rectangle(love.draw_line, self.x+self.width, self.y, self.bar_width, self.height)
    love.graphics.rectangle(love.draw_line, self.x, self.y, self.width, self.height)

end
