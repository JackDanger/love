AM_CPPFLAGS = $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE SDLTimer
lib_LTLIBRARIES = liblove_sdltimer.la
liblove_sdltimer_la_LDFLAGS = -lSDL
liblove_sdltimer_la_LIBADD = $(LIBLOVE)
liblove_sdltimer_la_SOURCES = \
love_sdltimer.cpp love_sdltimer.h \
mod_sdltimer.cpp mod_sdltimer.h
