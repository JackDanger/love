
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
	 
end

main.update = function(dt)
	
end

main.render = function()
	-- This causes C++ errlol.
	bazzle();
end