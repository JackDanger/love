AM_CPPFLAGS = $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE SDLMouse
lib_LTLIBRARIES = liblove_sdlmouse.la
liblove_sdlmouse_la_LDFLAGS = -lSDL
liblove_sdlmouse_la_LIBADD = $(LIBLOVE)
liblove_sdlmouse_la_SOURCES = \
love_sdlmouse.cpp love_sdlmouse.h \
mod_sdlmouse.cpp mod_sdlmouse.h

