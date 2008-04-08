TARGET = love_sdlkeyboard.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/sdlkeyboard
OBJ = $(OBJDIR)/love_sdlkeyboard.o \
$(OBJDIR)/mod.o \
$(OBJDIR)/mod_sdlkeyboard.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod.o: $(SRCDIR)/../mod.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/mod_sdlkeyboard.o: $(SRCDIR)/mod_sdlkeyboard.cpp
	$(CC) -fPIC -g0 -O2 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
