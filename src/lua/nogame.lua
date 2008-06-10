flash = 0
display = true
function load()
	if not love.graphics.isSet() then
		love.graphics.setMode(800, 600, false, true, 0)
	end
	love.graphics.setCaption("LOVE " .. love.system.getVersion() .. " (" .. love.system.getCodename() .. ")") 
	big = love.graphics.newFont(love.default_font, 24) 
	small = love.graphics.newFont(love.default_font, 12) 
	love.graphics.setBackgroundColor(151, 246, 15) 
	vermin = love.graphics.newImage(love.default_vermin) 
	logo = love.graphics.newImage(love.default_logo_256) 
end
r = 0 
function update(dt) 
	r = r + dt 
	flash = flash + dt 
	if flash > 0.8 then flash = 0; display = not display; end 
end 
function draw() 
	love.graphics.setFont(small) 
	love.graphics.draw(logo, 400, 280) 
	love.graphics.draw(vermin, 400, 380 + math.sin(r)*10) 
	love.graphics.drawf(love.system.getVersion() .. "\n" .. love.system.getCodename(), 480, 560, 300, love.align_right) 
	love.graphics.setFont(big) 
	if display then love.graphics.drawf("No Game", 300, 500, 200, love.align_center) end  
end