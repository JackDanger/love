-- Example: Line Iterators

function load()

	-- Set the font.
	love.graphics.setFont(love.default_font, 8)

	-- Store the lines in this table.
	lines = {}

	-- Open the file main.lua and loop through the first
	-- 50 lines.
	for line in love.filesystem.lines("main.lua") do
		table.insert(lines, line)
		if #lines >= 50 then break end
	end

end

function draw()
	-- Draw the loaded lines.
	for i = 1,#lines do
		love.graphics.draw("Line " .. i .. ": " .. lines[i], 50, 50+(i*10))
	end
end

