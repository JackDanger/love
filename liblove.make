TARGET = liblove
BINDIR = bin
OBJDIR = obj
SRCDIR = src/liblove
OBJ = $(OBJDIR)/arg.o \
$(OBJDIR)/Configuration.o \
$(OBJDIR)/Core.o \
$(OBJDIR)/Exception.o \
$(OBJDIR)/File.o \
$(OBJDIR)/Game.o \
$(OBJDIR)/Module.o \
$(OBJDIR)/MemoryFile.o \
$(OBJDIR)/Resource.o \
$(OBJDIR)/version.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1 -lSDL
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL -Isrc/liblove/include

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@.so $^
	ar crs $(BINDIR)/$@.a $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
