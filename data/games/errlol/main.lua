
main = {}

azzle = function()
	hizzle()
end

hizzle = function()
	fail.leetness = 5;
end


nazzle = function()
	azzle()
end

bazzle = function()
	nazzle()
end


main.load = function()
	
	local color = love.objects:newColor(255, 0, 0);
	print(color:getRed())
	
	local img = love.objects:newImage("button_default.png");
	local shit = img:getWidth();
	
	print(shit)
	

	

end

main.update = function(dt)

end

main.render = function()

end
