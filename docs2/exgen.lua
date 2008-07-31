

-- Formats input text as HTML'd
-- lua code.

function exget(n)
    local f = "examples/e".. exnum(n) .. ".lua"
    local e = io.open(f)
    if not e then error("Could not open file \"" .. f .. "\"") end
    local data = {}
    for line in e:lines() do
        table.insert(data, line)
    end
    io.close(e)
    return data
end

function exsub(text, s, class)
    
    local processed = string.gsub(" "..text.." ", "(%s)("..s..")([^%w_])",
        function (a, b,c)
            return a..'<span class="'..class..'">'..b..'</span>'..c
        end)
    return string.sub(processed, 2, string.len(processed)-1)
end

function exsubn(text, class, ...)
    local keywords = { ... }
    for i,k in ipairs(keywords) do
        text = exsub(text, k, class)
    end
    return text
end

function excomment(text)
    local s = string.find(text, "[-][-]")
    if s then
        text = string.sub(text, 1, s-1) ..  '<span class="comment">' .. string.sub(text, s) .. '</span>'
    end
    return text, s
end

function extitle(data)
    local s, e, m, m2 = string.find(data[1], "(%-%- Example: )(.*)")
    if s then
        table.remove(data, 1)
    end
    return m2
end

function exgen(data)

    local title = extitle(data)

    local s = false
    for i in ipairs(data) do
        data[i], s = excomment(data[i])
        if not s then
           
            data[i] = exsubn(data[i],
                "keyword",
                'break', 'do', 'end', 'else',
                'elseif', 'function', 'if', 'local',
                'nil', 'not', 'or', 'repeat',
                'return', 'then', 'until', 'while')
        end
    end
    return "<pre>"..trim(table.concat(data, "\n")).."</pre>", title
end

function exnum(n)
    local s = ""
    n = tonumber(n)
    local r = n
    if r <= 0 then error("Example IDs must be bigger than 0. (Got: " .. r .. ")") end
    if r >= 10000 then error("Example IDs must be less than 10000. (Got: " .. r .. ")") end
    while r < 1000 do
        s = s .. "0"
        r = r * 10
    end
    s = s .. n
    return s
end

