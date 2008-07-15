SUBDIRS = ./chipmunk/chipmunk
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I/usr/include/freetype2  $(INCLUDE_LUA) -I/usr/include/SDL -Iliblove/include

# LÖVE executable
bin_PROGRAMS = love
love_LDFLAGS = -lfreetype -lGL -lGLU -lIL -lILU -lILUT -lphysfs -lSDL -lSDL_mixer
love_LDADD = chipmunk/chipmunk/libchipmunk.a

love_SOURCES = love.cpp \
\
./chipmunk/mod_chipmunk.h \
./chipmunk/Body.cpp \
./chipmunk/Body.h \
./chipmunk/BoundingBox.cpp \
./chipmunk/BoundingBox.h \
./chipmunk/CircleShape.cpp \
./chipmunk/CircleShape.h \
./chipmunk/love_chipmunk.cpp \
./chipmunk/love_chipmunk.h \
./chipmunk/mod_chipmunk.cpp \
./chipmunk/PolygonShape.cpp \
./chipmunk/PolygonShape.h \
./chipmunk/SegmentShape.cpp \
./chipmunk/SegmentShape.h \
./chipmunk/Shape.cpp \
./chipmunk/Shape.h \
./chipmunk/Space.cpp \
./chipmunk/Space.h \
./chipmunk/Vector.cpp \
./chipmunk/Vector.h \
\
./liblove/arg.cpp \
./liblove/Configuration.cpp \
./liblove/Core.cpp \
./liblove/DynamicModule.cpp \
./liblove/Exception.cpp \
./liblove/File.cpp \
./liblove/Game.cpp \
./liblove/include/love/arg.h \
./liblove/include/love/Configuration.h \
./liblove/include/love/constants.h \
./liblove/include/love/Core.h \
./liblove/include/love/DynamicModule.h \
./liblove/include/love/events.h \
./liblove/include/love/Exception.h \
./liblove/include/love/File.h \
./liblove/include/love/Game.h \
./liblove/include/love/math.h \
./liblove/include/love/MemoryFile.h \
./liblove/include/love/mod.h \
./liblove/include/love/modspec.h \
./liblove/include/love/Module.h \
./liblove/include/love/platform.h \
./liblove/include/love/Resource.h \
./liblove/include/love/StaticModule.h \
./liblove/include/love/Vector.h \
./liblove/include/love/version.h \
./liblove/MemoryFile.cpp \
./liblove/modspec.cpp \
./liblove/Module.cpp \
./liblove/Resource.cpp \
./liblove/StaticModule.cpp \
./liblove/Vector.cpp \
./liblove/version.cpp \
\
./opengl/love_opengl.cpp \
./opengl/Animation.cpp \
./opengl/Animation.h \
./opengl/Color.cpp \
./opengl/Color.h \
./opengl/Font.cpp \
./opengl/Font.h \
./opengl/GLee.c \
./opengl/GLee.h \
./opengl/Image.cpp \
./opengl/Image.h \
./opengl/ImageFont.cpp \
./opengl/ImageFont.h \
./opengl/love_opengl.h \
./opengl/mod_opengl.cpp \
./opengl/mod_opengl.h \
./opengl/ParticleSystem.cpp \
./opengl/ParticleSystem.h \
./opengl/PointParticleSystem.cpp \
./opengl/PointParticleSystem.h \
./opengl/resources.cpp \
./opengl/resources.h \
./opengl/Sprite.cpp \
./opengl/Sprite.h \
./opengl/TrueTypeFont.cpp \
./opengl/TrueTypeFont.h \
./opengl/Volatile.cpp \
./opengl/Volatile.h \
\
./physfs/File.cpp \
./physfs/File.h \
./physfs/love_physfs.cpp \
./physfs/love_physfs.h \
./physfs/mod_physfs.cpp \
./physfs/mod_physfs.h \
\
./sdlkeyboard/love_sdlkeyboard.cpp \
./sdlkeyboard/love_sdlkeyboard.h \
./sdlkeyboard/mod_sdlkeyboard.cpp \
./sdlkeyboard/mod_sdlkeyboard.h \
\
./sdlmixer/love_sdlmixer.cpp \
./sdlmixer/love_sdlmixer.h \
./sdlmixer/mod_sdlmixer.cpp \
./sdlmixer/mod_sdlmixer.h \
./sdlmixer/Music.cpp \
./sdlmixer/Music.h \
./sdlmixer/Sound.cpp \
./sdlmixer/Sound.h \
\
./sdlmouse/love_sdlmouse.cpp \
./sdlmouse/love_sdlmouse.h \
./sdlmouse/mod_sdlmouse.cpp \
./sdlmouse/mod_sdlmouse.h \
\
./sdltimer/love_sdltimer.cpp \
./sdltimer/love_sdltimer.h \
./sdltimer/mod_sdltimer.cpp \
./sdltimer/mod_sdltimer.h \
\
./system/love_system.cpp \
./system/love_system.h \
./system/LuaGame.cpp \
./system/LuaGame.h \
./system/mod_system.cpp \
./system/mod_system.h \
./system/resources.cpp \
./system/resources.h
