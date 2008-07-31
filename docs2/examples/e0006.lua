-- Example: Cursor Visibility
function load()
    -- Hide mouse on startup.
    love.mouse.setVisible(false)
end

-- Toggle cursor visibility.
function keypressed()
    if love.mouse.isVisible() then
        love.mouse.setVisible(false)
    else
        love.mouse.setVisible(true)
    end
end