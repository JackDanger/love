TARGET = love_system.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/system
OBJ = $(OBJDIR)/love_system.o \
$(OBJDIR)/mod.o \
$(OBJDIR)/mod_system.o \
$(OBJDIR)/version.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/../%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/mod_system.o: $(SRCDIR)/mod_system.cpp
	$(CC) -fPIC -g0 -O2 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
