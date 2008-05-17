TARGET = love_sdlmouse.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/sdlmouse
OBJ = $(OBJDIR)/love_sdlmouse.o \
$(OBJDIR)/mod_sdlmouse.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ) $(BINDIR)/liblove.a
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod_sdlmouse.o: $(SRCDIR)/mod_sdlmouse.cpp
	$(CC) -fPIC -g0 -O3 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
