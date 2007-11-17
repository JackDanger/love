swig -lua -c++ -o "../../../../src/love_lua_glue.cpp" -I"../../../../src" -I"../include" -I"../include/lua" ../../../../swig/love.i
echo #include "lua_glue_bot.h" >> "../../../../src/love_lua_glue.cpp"
"../php/php.exe" create_types.php
"../php/php.exe" fix_warnings.php
pause