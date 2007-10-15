
--
-- Font test game
--

main = {
     
       load = function()

            game:addFont("verdana", 12);
            game:addFont("lacuna", 40);
            game:addFont("times", 20);


            max_fonts = 18;

            for i=0, max_fonts, 1 do
                game:addFont("arial" .. i, 8 + i);
            end

            game:addColor("black", 0, 0, 0)
            game:addColor("red", 255, 0, 0);
            game:addColor("blue", 0x0033CC);
            game:addColor("green", 0x009933);

            game:setColor("black");
            game:setBackground(game:addColor("white", 255, 255, 255));

            fox = "The quick brown fox jumped over the lazy dog.";

       end,
       
       render = function()
       
              game:setColor("black");
              game:setFont("verdana");
              game:drawString(50, 50, fox);

              game:setColor("blue");
              game:setFont("times");
              game:drawString(50, 80, fox);

              game:setColor("red");
              game:setFont("lacuna");
              game:drawString(50, 130, fox);

              game:setColor("black");

              for i=0, max_fonts, 1 do
                  game:setFont("arial" .. i);
                  game:drawString(50, 200 + (i * 30), (i+8) .. ": " .. fox);
              end



       end,

       keypressed = function(key)
                  if key == LOVE_KEY_LEFT then
                  end
       end

}