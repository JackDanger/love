
state2 = {

	t = 0,
	init = function()
		print("State 2 init lol!\n");
		
	end,
	update = function(dt)
	
		hamster_ai.speed = -50;
	
		state2.t = state2.t + dt;
		if state2.t > 2 then 
			game:setState("sys_gs_main") 
			state2.t = state2.t -2;
		end;
	end, 
	render = function()
		game:drawString(150, 70, "This is state2!");
	end	
}