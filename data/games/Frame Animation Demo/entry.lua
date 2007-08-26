
alpha = 0
num = 8

main = {

	init = function()
	
		-- Add the image used as the source for the animation.
		game:addImage("image-explode", "Explosion_1.png");
		
		-- Add the FrameAnimation™ itself, and save the pointer.
		-- The name of the wanted source image is passed as the second parameter.
		local f = game:addFrameAnimation("fa-explode", "image-explode");
		
		-- Build frames
		-- Syntax: width in frames, height in frames, frame width in px, frame height in px, time between each frame in secs.
		-- Frame order is top left to bottom right.
		f:addFrames(5, 3, 96, 96, 0.04);
		f:start();
		
	end, 

	update = function(dt)

		-- Update animation
		game:getFrameAnimation("fa-explode"):update(dt);
		
		alpha = alpha + 90 * dt;

	end, 

	render = function()

		gl:loadIdentity();

		-- Render full image
		--game:getImage("image-explode"):render();
		
		gl:translate(512, 356);
		
		gl:rotate(alpha);
		
		local i = 0;
		
		while i < num do
		
			gl:pushMatrix();
			
			gl:translate(-48, -48);
			
			gl:rotate(-2*alpha);
			
			-- Render animation
			game:getFrameAnimation("fa-explode"):render();
			gl:popMatrix();
			
			gl:translate(3 * i, 20);
			
			i = i + 1;
			
		end

	end, -- Render
	

	
	keyreleased = function(key)
	
		if key == LOVE_KEY_s then 
			game:getFrameAnimation("fa-explode"):start(); 
		end
		
		if key == LOVE_KEY_d then 
			game:getFrameAnimation("fa-explode"):stop(); 
		end
		
		if key == LOVE_KEY_UP then 
			num = num + 1
		end
		
		if key == LOVE_KEY_DOWN then 
			num = num - 1
		end
		
	end
	


}