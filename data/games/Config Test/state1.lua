


state1 = {

	t = 0, 

	init = function()
		game:include("state2.lua");
		print("State 1 init lol!\n");
		
	end,
	update = function(dt)
	
		hamster_ai.speed = 100;
	
		state1.t = state1.t + dt;
		
		if state1.t > 3 then 
			game:setState("state2");
			state1.t = state1.t - 3;
		end;
	
	end, 
	render = function()
		game:drawString(150, 50, "This is state1!!!1ineineioneon!!!e");
	end	
}