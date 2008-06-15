AM_CPPFLAGS = $(INCLUDE_LUA) $(INCLUDE_LOVE)

# LÖVE PhysFS
lib_LTLIBRARIES = liblove_physfs.la
liblove_physfs_la_LDFLAGS = -lphysfs
liblove_physfs_la_LIBADD = $(LIBLOVE)
liblove_physfs_la_SOURCES = \
File.cpp File.h \
love_physfs.cpp love_physfs.h \
mod_physfs.cpp mod_physfs.h
