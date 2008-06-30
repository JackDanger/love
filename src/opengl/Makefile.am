AM_CPPFLAGS = -I/usr/include/freetype2  $(INCLUDE_LUA) -I/usr/include/SDL $(INCLUDE_LOVE)

# LÖVE OpenGL
lib_LTLIBRARIES = liblove_opengl.la
liblove_opengl_la_LDFLAGS = -lfreetype -lGL -lGLU -lIL -lILU -lILUT -lphysfs -lSDL -lSDL_mixer
liblove_opengl_la_LIBADD = $(LIBLOVE)
liblove_opengl_la_SOURCES = \
Animation.cpp Animation.h \
Color.cpp Color.h \
Font.cpp Font.h \
GLee.c GLee.h \
Image.cpp Image.h \
ImageFont.cpp ImageFont.h \
ParticleSystem.cpp ParticleSystem.h \
PointParticleSystem.cpp PointParticleSystem.h \
Sprite.cpp Sprite.h \
TrueTypeFont.cpp TrueTypeFont.h \
Volatile.cpp Volatile.h \
love_opengl.cpp love_opengl.h \
mod_opengl.cpp mod_opengl.h \
resources.cpp resources.h
