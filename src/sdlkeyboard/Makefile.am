AM_CPPFLAGS = $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE SDLKeyboard
lib_LTLIBRARIES = liblove_sdlkeyboard.la
liblove_sdlkeyboard_la_LDFLAGS = -lSDL
liblove_sdlkeyboard_la_LIBADD = $(LIBLOVE)
liblove_sdlkeyboard_la_SOURCES = \
love_sdlkeyboard.cpp love_sdlkeyboard.h \
mod_sdlkeyboard.cpp mod_sdlkeyboard.h
