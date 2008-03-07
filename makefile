TARGET = love
BINDIR = .
OBJDIR = obj
SRCDIR = src
OBJ = $(OBJDIR)/AnimatedColor.o \
$(OBJDIR)/Animation.o \
$(OBJDIR)/Audio.o \
$(OBJDIR)/Color.o \
$(OBJDIR)/Button.o \
$(OBJDIR)/balance.o \
$(OBJDIR)/Configuration.o \
$(OBJDIR)/Device.o \
$(OBJDIR)/Display.o \
$(OBJDIR)/File.o \
$(OBJDIR)/Filesystem.o \
$(OBJDIR)/Font.o \
$(OBJDIR)/FontTexGame.o \
$(OBJDIR)/Game.o \
$(OBJDIR)/Graphics.o \
$(OBJDIR)/Image.o \
$(OBJDIR)/Keyboard.o \
$(OBJDIR)/love.o \
$(OBJDIR)/love_arg.o \
$(OBJDIR)/love_math.o \
$(OBJDIR)/love_version.o \
$(OBJDIR)/Label.o \
$(OBJDIR)/LuaGame.o \
$(OBJDIR)/lualove_glue.o \
$(OBJDIR)/LuaVM.o \
$(OBJDIR)/main.o \
$(OBJDIR)/Matrix.o \
$(OBJDIR)/MemoryFile.o \
$(OBJDIR)/Mouse.o \
$(OBJDIR)/Music.o \
$(OBJDIR)/NoGame.o \
$(OBJDIR)/OpenGLFont.o \
$(OBJDIR)/OpenGLGraphics.o \
$(OBJDIR)/OpenGLImage.o \
$(OBJDIR)/OpenGLImageFont.o \
$(OBJDIR)/OpenGLParticleSystem.o \
$(OBJDIR)/Particlesystem.o \
$(OBJDIR)/PhysFSFile.o \
$(OBJDIR)/PhysFSFilesystem.o \
$(OBJDIR)/platform_sdl.o \
$(OBJDIR)/Resource.o \
$(OBJDIR)/resources.o \
$(OBJDIR)/SDLDisplay.o \
$(OBJDIR)/SDLKeyboard.o \
$(OBJDIR)/SDLMixerAudio.o \
$(OBJDIR)/SDLMixerMusic.o \
$(OBJDIR)/SDLMixerSound.o \
$(OBJDIR)/SDLMouse.o \
$(OBJDIR)/SDLTimer.o \
$(OBJDIR)/Sound.o \
$(OBJDIR)/Sprite.o \
$(OBJDIR)/Timer.o \
$(OBJDIR)/Vector.o \
$(OBJDIR)/Widget.o

CC = g++
CFLAGS = -g -O0 -Wall -Wno-unused-label -fno-strict-aliasing
LDFLAGS = -lGL -lGLU -lIL -lILU -lILUT -lSDL -lSDL_mixer -llua5.1 -lphysfs -lfreetype -lboost_filesystem
INCLUDES = -I/usr/include/freetype2 -I/usr/include/lua5.1 -I/usr/include/SDL

default: prep $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

prep:
	mkdir $(OBJDIR) &> /dev/null

clean:
	rm -f $(OBJ)
