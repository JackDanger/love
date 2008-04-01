TARGET = love_sdltimer.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/sdltimer
OBJ = $(OBJDIR)/love_sdltimer.o \
$(OBJDIR)/mod.o \
$(OBJDIR)/mod_sdltimer.o

CC = g++
CFLAGS = -g -O2 -Wall -Wno-unused-label -fno-strict-aliasing
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod.o: $(SRCDIR)/../mod.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
