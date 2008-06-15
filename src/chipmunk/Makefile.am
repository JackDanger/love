AM_CPPFLAGS = $(INCLUDE_LUA) $(INCLUDE_LOVE)
SUBDIRS = chipmunk

# LÖVE Chipmunk
# src/chipmunk
lib_LTLIBRARIES = liblove_chipmunk.la
liblove_chipmunk_la_LIBADD = chipmunk/libchipmunk.a $(LIBLOVE)
liblove_chipmunk_la_SOURCES = \
Body.cpp Body.h \
love_chipmunk.cpp love_chipmunk.h \
mod_chipmunk.cpp mod_chipmunk.h \
Shape.cpp Shape.h \
Space.cpp Space.h
