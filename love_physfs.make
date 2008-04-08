TARGET = love_physfs.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/physfs
OBJ = $(OBJDIR)/love_physfs.o \
$(OBJDIR)/physfs_File.o \
$(OBJDIR)/mod_physfs.o \
$(OBJDIR)/modfs.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -lboost_filesystem -llua5.1 -lphysfs -lSDL 
INCLUDES = -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/modfs.o: $(SRCDIR)/../modfs.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/physfs_File.o: $(SRCDIR)/File.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/mod_physfs.o: $(SRCDIR)/mod_physfs.cpp
	$(CC) -fPIC -g0 -O2 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
