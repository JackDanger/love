swig -nodefaultctor -lua -c++ -o "../../../../src/lualove_glue.cpp" -I"../../../../src" -I"../include" -I"../include/lua" ../../../../swig/love.i
"../php/php.exe" post.php
pause