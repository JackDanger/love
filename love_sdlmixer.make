TARGET = love_sdlmixer.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/sdlmixer
OBJ = $(OBJDIR)/love_sdlmixer.o \
$(OBJDIR)/mod_sdlmixer.o \
$(OBJDIR)/Music.o \
$(OBJDIR)/Sound.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL -lSDL_mixer
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ) $(BINDIR)/liblove.a
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod_sdlmixer.o: $(SRCDIR)/mod_sdlmixer.cpp
	$(CC) -fPIC -g0 -O3 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
