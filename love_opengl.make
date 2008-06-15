TARGET = liblove_opengl.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/opengl
OBJ = $(OBJDIR)/Animation.o \
$(OBJDIR)/Color.o \
$(OBJDIR)/console.o \
$(OBJDIR)/Font.o \
$(OBJDIR)/Image.o \
$(OBJDIR)/ImageFont.o \
$(OBJDIR)/love_opengl.o \
$(OBJDIR)/mod_opengl.o \
$(OBJDIR)/ParticleSystem.o \
$(OBJDIR)/PointParticleSystem.o \
$(OBJDIR)/resources.o \
$(OBJDIR)/Sprite.o \
$(OBJDIR)/TrueTypeFont.o \
$(OBJDIR)/Volatile.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -lfreetype -lGL -lGLU -lIL -lILU -lILUT -llua5.1 -lphysfs -lSDL -lSDL_mixer
INCLUDES = -I/usr/include/freetype2 -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ) $(BINDIR)/liblove.a
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod_opengl.o: $(SRCDIR)/mod_opengl.cpp
	$(CC) -fPIC -g0 -O3 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
