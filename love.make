TARGET = love
BINDIR = bin
OBJDIR = obj
SRCDIR = src
OBJ = $(OBJDIR)/Audio.o \
$(OBJDIR)/Configuration.o \
$(OBJDIR)/Exception.o \
$(OBJDIR)/File.o \
$(OBJDIR)/Filesystem.o \
$(OBJDIR)/Game.o \
$(OBJDIR)/Graphics.o \
$(OBJDIR)/Keyboard.o \
$(OBJDIR)/love_arg.o \
$(OBJDIR)/love.o \
$(OBJDIR)/LuaGame.o \
$(OBJDIR)/LuaVM.o \
$(OBJDIR)/main.o \
$(OBJDIR)/MemoryFile.o \
$(OBJDIR)/Module.o \
$(OBJDIR)/Mouse.o \
$(OBJDIR)/NoGame.o \
$(OBJDIR)/Physics.o \
$(OBJDIR)/Resource.o \
$(OBJDIR)/SuspendGame.o \
$(OBJDIR)/System.o \
$(OBJDIR)/Timer.o \
$(OBJDIR)/version.o \
$(OBJDIR)/Volatile.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
