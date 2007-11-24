
main = {
	
	load = function()

		-- variables
		font = { 
			vera10 = love.objects:newFont("Vera.ttf", 10), 
			vera8 = love.objects:newFont("Vera.ttf", 8), 
			vera10b = love.objects:newFont("VeraBd.ttf", 10), 
			vera8b = love.objects:newFont("VeraBd.ttf", 8), 
			vera10i = love.objects:newFont("VeraIt.ttf", 10), 
			vera8i = love.objects:newFont("VeraIt.ttf", 8), 
			free10 = love.objects:newDefaultFont(10), 
			free8 = love.objects:newDefaultFont(8), 
			imgf = love.objects:newImageFont("techyfontwhite.png", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`´*#=[]\"")
			} 
			
			
		color = { 
			white = love.objects:newColor(0xFFFFFF), 
			yoga = love.objects:newColor(0x57a1d3)
			}

		
		love.graphics:setBackgroundColor(color.yoga);
		love.graphics:setColor(color.white);
		
		str = "In this comparison, we clearly see that Vera seems to work better with FreeType2 at small sizes. The glyphs in Vera are simply easier to read. I think Vera-10 should be the default GUI font in LOVE, as it appears to be more readable.";

		
	end,
	render = function()
	
	
		love.graphics:setFont(font.vera10)
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-10)", 50, 120);
		
		love.graphics:setFont(font.free10)
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (FreeSans-10)", 50, 135);
		
		love.graphics:setFont(font.vera8)
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-8)", 50, 160);
		
		love.graphics:setFont(font.free8)
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (FreeSans-8)", 50, 170);
		
		love.graphics:setFont(font.vera10b);
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-10 bold)", 50, 200);
		love.graphics:setFont(font.vera10i);
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-10 italic)", 50, 215);
		
		love.graphics:setFont(font.vera8b);
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-8 bold)", 50, 240);
		love.graphics:setFont(font.vera8i);
		love.graphics:draw("The quick brown fox jumped over the whatindahwho? (Vera-8 italic)", 50, 250);
		

		love.graphics:setFont(font.vera10)
		love.graphics:draw(str, 50, 300, 200);
		
		love.graphics:setFont(font.free10)
		love.graphics:draw(str, 300, 300, 200);
		
		love.graphics:setFont(font.imgf)
		love.graphics:draw("And of course, I had to test the new ImageFont. This kicks immense amounts of ass. ", 50, 450, 400);
		
	end

} -- main
