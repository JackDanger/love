
-- SHapes demo

main = {

	init = function()
	
		game:addColor("RED", 255, 0, 0);
		game:addColor("BLUE", 0, 0, 255);
		game:addColor("WHITE", 255, 255, 255);
		game:addColor("BLACK", 0);
		game:addColor("GREEN", 0, 255, 0);
		
		game:addColor("inner", 0x8fa6b1);
	
		game:setBackground("BLACK");
		game:setColor("RED");
		
		game:addRectangle("rect1", 200, 50);
		game:addCircle("c1", 200);
		
		game:addCircle("bc", 50);
		game:addCircle("bcb", 60);
		
		
		p = game:addPolygon("p1");
		p:addPoint(-50, -50);
		p:addPoint(0, 50);
		p:addPoint(50, -50);
		
		rotation = 0;
		
	end,
	
	update = function(dt)
		
		rotation = rotation + (50 * 3.14 * dt);
		
	end,
	
	render = function()
		
		--gl:enable("POLYGON_SMOOTH");
		--gl:hint("POLYGON_SMOOTH_HINT", "NICEST");
		--gl:shadeModel("SMOOTH");
		--gl:enable("LINE_SMOOTH");

				
	
		
		game:setColor("RED");
		game:fill("rect1", 50, 50);
		
		game:setColor("BLUE");
		game:fill("c1", 300, 400);		


		gl:pushMatrix();
			gl:scale(0.5, 0.5);
			game:setColor("GREEN");
			game:draw("c1", 700, 400);
		gl:popMatrix();
		
		
		gl:enable("MULTISAMPLE");
		game:setColor("WHITE");
		game:fill("bcb", 700, 400);		
		game:setColor("inner");
		game:fill("bc", 700, 400);
		gl:disable("MULTISAMPLE");

		

		
		

		

		gl:pushMatrix();
			gl:translate(800,600);
			gl:rotate(rotation);
			game:setColor("WHITE");
			game:fill("p1");
		gl:popMatrix();
		
		
		gl:disable("POLYGON_SMOOTH");		
		
		
	end
}