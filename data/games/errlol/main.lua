
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
	-- This causes C++ error when the game is restarted after clicking "OK".
	 bazzle();
end

main.update = function(dt)
	 bazzle();
end

main.render = function()
	 bazzle();
end