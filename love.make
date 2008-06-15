TARGET = love
BINDIR = bin
OBJDIR = obj
SRCDIR = src
OBJ = $(OBJDIR)/love.o

CC = g++
CFLAGS = -g0 -O3 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ) $(BINDIR)/liblove.a
	$(CC) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
