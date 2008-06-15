AM_CPPFLAGS = $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE System
lib_LTLIBRARIES = liblove_system.la
liblove_system_la_LDFLAGS = -lSDL
liblove_system_la_LIBADD = $(LIBLOVE)
liblove_system_la_SOURCES = \
LuaGame.cpp LuaGame.h \
love_system.cpp love_system.h \
mod_system.cpp mod_system.h \
resources.cpp resource.h
