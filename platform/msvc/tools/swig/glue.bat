swig -lua -c++ -o "../src/love_lua_glue.cpp" -I"../src" -I"../include" -I"../include/lua" -I"../src" love.i
echo #include "lua_glue_bot.h" >> "../src/love_lua_glue.cpp"
"../../tools/php/php.exe" create_types.php
"../../tools/php/php.exe" fix_warnings.php
pause