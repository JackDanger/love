TARGET = love_sdlmixer.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/sdlmixer
OBJ = $(OBJDIR)/love_sdlmixer.o \
$(OBJDIR)/modfs.o \
$(OBJDIR)/mod_sdlmixer.o \
$(OBJDIR)/Music.o \
$(OBJDIR)/Sound.o

CC = g++
CFLAGS = -g -O2 -Wall -Wno-unused-label -fno-strict-aliasing
LDFLAGS = -llua5.1 -lSDL -lSDL_mixer
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/modfs.o: $(SRCDIR)/../modfs.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
