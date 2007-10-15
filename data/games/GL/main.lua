
main = {

	

	load = function()
	
		game:addColor("white", 0xffffff);
	
		game:setColor("white");
		game:setBackground(game:addColor("black", 0));
		
		
		alpha = 0;
		
	end,
	
	update = function(dt)
	
		alpha = alpha + (3.14 * dt);
	
	end, 
	
	render = function()
	
		--gl:enable("POLYGON_SMOOTH");
		--gl:hint("POLYGON_SMOOTH_HINT", "NICEST");
		gl:shadeModel("SMOOTH");
		
		
		game:drawString(240, 200,"No FSAA");
		game:drawString(640, 200,"4 x FSAA");
		
		
		gl:enable("MULTISAMPLE");
		gl:disable("TEXTURE");

		
	
		gl:loadIdentity();
		gl:translate(700,768/2);
		gl:scale(2,2);
		
		gl:pushMatrix()
			gl:rotate(alpha);
			gl:begin("QUADS");
				gl:color(255,0,0);gl:vertex(-50,-50);
				gl:color(0,255,0);gl:vertex(-50,50);
				gl:color(0,0,255);gl:vertex(50,50);
				gl:color(0,0,255);gl:vertex(50,-50);
			gl:finish();
		gl:popMatrix();
		
		gl:loadIdentity();
		gl:translate(300,768/2);
		gl:scale(2,2);
		
		gl:disable("MULTISAMPLE");
		
		gl:pushMatrix()
			gl:rotate(alpha);
			gl:begin("QUADS");
				gl:color(255,0,0);gl:vertex(-50,-50);
				gl:color(0,255,0);gl:vertex(-50,50);
				gl:color(0,0,255);gl:vertex(50,50);
				gl:color(0,0,255);gl:vertex(50,-50);
			gl:finish();
		gl:popMatrix();
		

		
		
		--gl:disable("POLYGON_SMOOTH");	
		
	
	end
	
}