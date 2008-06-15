AM_CPPFLAGS = $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE SDLMixer
lib_LTLIBRARIES = liblove_sdlmixer.la
liblove_sdlmixer_la_LDFLAGS = -lSDL -lSDL_mixer
liblove_sdlmixer_la_LIBADD = $(LIBLOVE)
liblove_sdlmixer_la_SOURCES = \
Music.cpp Music.h \
Sound.cpp Sound.h \
love_sdlmixer.cpp love_sdlmixer.h \
mod_sdlmixer.cpp mod_sdlmixer.h
