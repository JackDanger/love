######################################################################
# "Ancient" LOVE makefile. (Works for 0.3-2)
# You may need to modify parts of this makefile for your system.
######################################################################

CC = g++
CFLAGS = -g -O2 -Wall
CFLAGS_MOD = -g0 -O3
BINDIR = bin

# Inclusion paths.
INCLUDE_SDL = -I/usr/include/SDL
INCLUDE_LUA = -I/usr/include/lua5.1
INCLUDE_LIBLOVE = -Isrc/liblove/include
INCLUDE_FREETYPE = -I/usr/include/freetype2

# Linker flags.
LD_LUA = -llua5.1
LD_SDL = -lSDL
LD_PHYSFS = -lphysfs
LD_FREETYPE = -lfreetype
LD_GL = -lGL -lGLU
LD_IL = -lIL -lILU
LD_SDLMIXER = -lSDL_mixer

######################################################################

default: prep $(BINDIR)/liblove.a love

INCLUDE_COMMON = $(INCLUDE_LUA) $(INCLUDE_SDL) $(INCLUDE_LIBLOVE)
LD_COMMON = $(LD_LUA) $(LD_SDL)

#
# liblove
#

LIBLOVE_TARGET = $(BINDIR)/liblove.a
LIBLOVE_OBJDIR = obj/liblove
LIBLOVE_SRCDIR = src/liblove
LIBLOVE_OBJ = $(LIBLOVE_OBJDIR)/arg.o \
$(LIBLOVE_OBJDIR)/Configuration.o \
$(LIBLOVE_OBJDIR)/Core.o \
$(LIBLOVE_OBJDIR)/DynamicModule.o \
$(LIBLOVE_OBJDIR)/StaticModule.o \
$(LIBLOVE_OBJDIR)/Exception.o \
$(LIBLOVE_OBJDIR)/File.o \
$(LIBLOVE_OBJDIR)/Game.o \
$(LIBLOVE_OBJDIR)/modspec.o \
$(LIBLOVE_OBJDIR)/Module.o \
$(LIBLOVE_OBJDIR)/MemoryFile.o \
$(LIBLOVE_OBJDIR)/Resource.o \
$(LIBLOVE_OBJDIR)/version.o

LIBLOVE_INCLUDES = $(INCLUDE_SDL) $(INCLUDE_LIBLOVE)

$(LIBLOVE_TARGET): $(LIBLOVE_OBJ)
	ar crs $@ $^

$(LIBLOVE_OBJDIR)/%.o: $(LIBLOVE_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(LIBLOVE_INCLUDES) -c $< -o $@
	
	
# SDLTimer.
SDLTIMER_OBJDIR = obj/sdltimer
SDLTIMER_SRCDIR = src/sdltimer
SDLTIMER_OBJ = \
	$(SDLTIMER_OBJDIR)/love_sdltimer.o \
	$(SDLTIMER_OBJDIR)/mod_sdltimer.o

$(SDLTIMER_OBJDIR)/%.o: $(SDLTIMER_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(SDLTIMER_OBJDIR)/mod_sdltimer.o: $(SDLTIMER_SRCDIR)/mod_sdltimer.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@
	
# PhysFS
PHYSFS_OBJDIR = obj/physfs
PHYSFS_SRCDIR = src/physfs
PHYSFS_OBJ = \
	$(PHYSFS_OBJDIR)/love_physfs.o \
	$(PHYSFS_OBJDIR)/File.o \
	$(PHYSFS_OBJDIR)/mod_physfs.o

$(PHYSFS_OBJDIR)/%.o: $(PHYSFS_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(PHYSFS_OBJDIR)/mod_physfs.o: $(PHYSFS_SRCDIR)/mod_physfs.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@

# OpenGL
OPENGL_OBJDIR = obj/opengl
OPENGL_SRCDIR = src/opengl
OPENGL_OBJ = \
	$(OPENGL_OBJDIR)/Animation.o \
	$(OPENGL_OBJDIR)/Color.o \
	$(OPENGL_OBJDIR)/Font.o \
	$(OPENGL_OBJDIR)/GLee.o \
	$(OPENGL_OBJDIR)/Image.o \
	$(OPENGL_OBJDIR)/ImageFont.o \
	$(OPENGL_OBJDIR)/love_opengl.o \
	$(OPENGL_OBJDIR)/mod_opengl.o \
	$(OPENGL_OBJDIR)/ParticleSystem.o \
	$(OPENGL_OBJDIR)/PointParticleSystem.o \
	$(OPENGL_OBJDIR)/resources.o \
	$(OPENGL_OBJDIR)/Sprite.o \
	$(OPENGL_OBJDIR)/TrueTypeFont.o \
	$(OPENGL_OBJDIR)/Volatile.o

$(OPENGL_OBJDIR)/GLee.o: $(OPENGL_SRCDIR)/GLee.c
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) $(INCLUDE_FREETYPE) -c $< -o $@

$(OPENGL_OBJDIR)/%.o: $(OPENGL_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) $(INCLUDE_FREETYPE) -c $< -o $@
	
$(OPENGL_OBJDIR)/mod_opengl.o: $(OPENGL_SRCDIR)/mod_opengl.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) $(INCLUDE_FREETYPE) -c $< -o $@
	
# SDLKeyboard
SDLKEYBOARD_OBJDIR = obj/sdlkeyboard
SDLKEYBOARD_SRCDIR = src/sdlkeyboard
SDLKEYBOARD_OBJ = \
	$(SDLKEYBOARD_OBJDIR)/love_sdlkeyboard.o \
	$(SDLKEYBOARD_OBJDIR)/mod_sdlkeyboard.o

$(SDLKEYBOARD_OBJDIR)/%.o: $(SDLKEYBOARD_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(SDLKEYBOARD_OBJDIR)/mod_sdlkeyboard.o: $(SDLKEYBOARD_SRCDIR)/mod_sdlkeyboard.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@
	
# SDLMouse
SDLMOUSE_OBJDIR = obj/sdlmouse
SDLMOUSE_SRCDIR = src/sdlmouse
SDLMOUSE_OBJ = \
	$(SDLMOUSE_OBJDIR)/love_sdlmouse.o \
	$(SDLMOUSE_OBJDIR)/mod_sdlmouse.o

$(SDLMOUSE_OBJDIR)/%.o: $(SDLMOUSE_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(SDLMOUSE_OBJDIR)/mod_sdlmouse.o: $(SDLMOUSE_SRCDIR)/mod_sdlmouse.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@
	
# SDLMixer
SDLMIXER_OBJDIR = obj/sdlmixer
SDLMIXER_SRCDIR = src/sdlmixer
SDLMIXER_OBJ = \
	$(SDLMIXER_OBJDIR)/love_sdlmixer.o \
	$(SDLMIXER_OBJDIR)/mod_sdlmixer.o \
	$(SDLMIXER_OBJDIR)/Music.o \
	$(SDLMIXER_OBJDIR)/Sound.o

$(SDLMIXER_OBJDIR)/%.o: $(SDLMIXER_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(SDLMIXER_OBJDIR)/mod_sdlmixer.o: $(SDLMIXER_SRCDIR)/mod_sdlmixer.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@
	
# System

SYSTEM_OBJDIR = obj/system
SYSTEM_SRCDIR = src/system
SYSTEM_OBJ = \
	$(SYSTEM_OBJDIR)/love_system.o \
	$(SYSTEM_OBJDIR)/LuaGame.o \
	$(SYSTEM_OBJDIR)/resources.o \
	$(SYSTEM_OBJDIR)/mod_system.o

$(SYSTEM_OBJDIR)/%.o: $(SYSTEM_SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDE_COMMON) -c $< -o $@
	
$(SYSTEM_OBJDIR)/mod_system.o: $(SYSTEM_SRCDIR)/mod_system.cpp
	$(CC) -fPIC $(CFLAGS_MOD) $(INCLUDE_COMMON) -c $< -o $@
	
#
# LOVE (main binary)
#

LOVE_TARGET = love
LOVE_OBJDIR = obj/love
LOVE_SRCDIR = src
LOVE_OBJ = $(LOVE_OBJDIR)/love.o

LOVE_LDFLAGS = $(LD_SDL) $(LD_LUA) $(LD_PHYSFS) $(LD_FREETYPE) $(LD_GL) $(LD_IL) $(LD_SDLMIXER)
LOVE_INCLUDES = $(INCLUDE_LUA) $(INCLUDE_SDL) $(INCLUDE_LIBLOVE)

$(LOVE_TARGET): $(LOVE_OBJ) $(LIBLOVE_OBJ) $(SDLTIMER_OBJ) $(PHYSFS_OBJ) \
		  $(OPENGL_OBJ) $(SDLKEYBOARD_OBJ) $(SDLMOUSE_OBJ) \
		  $(SDLMIXER_OBJ) $(SYSTEM_OBJ)
	$(CC) $(LOVE_LDFLAGS) -o $(BINDIR)/$@ $^

$(LOVE_OBJDIR)/%.o: $(LOVE_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(LOVE_INCLUDES) -c $< -o $@


clean:
	rm -f $(LIBLOVE_OBJ) $(LOVE_OBJ) $(SDLTIMER_OBJ) $(PHYSFS_OBJ) \
		  $(OPENGL_OBJ) $(SDLKEYBOARD_OBJ) $(SDLMOUSE_OBJ) \
		  $(SDLMIXER_OBJ) $(SYSTEM_OBJ)
	rm -f $(BINDIR)/liblove.a $(BINDIR)/love
	
prep:
	mkdir -p obj bin obj/liblove obj/love obj/sdltimer obj/physfs \
		     obj/opengl obj/sdlkeyboard obj/sdlmouse obj/sdlmixer \
		     obj/chipmunk obj/system 
	
