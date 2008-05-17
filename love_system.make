TARGET = love_system.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/system
OBJ = $(OBJDIR)/love_system.o \
$(OBJDIR)/mod_system.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/mod_system.o: $(SRCDIR)/mod_system.cpp
	$(CC) -fPIC -g0 -O3 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
