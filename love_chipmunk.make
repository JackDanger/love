TARGET = liblove_chipmunk.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src/chipmunk
OBJ = $(OBJDIR)/chipmunk/chipmunk.o \
$(OBJDIR)/chipmunk/cpArbiter.o \
$(OBJDIR)/chipmunk/cpArray.o \
$(OBJDIR)/chipmunk/cpBB.o \
$(OBJDIR)/chipmunk/cpBody.o \
$(OBJDIR)/chipmunk/cpCollision.o \
$(OBJDIR)/chipmunk/cpHashSet.o \
$(OBJDIR)/chipmunk/cpJoint.o \
$(OBJDIR)/chipmunk/cpPolyShape.o \
$(OBJDIR)/chipmunk/cpShape.o \
$(OBJDIR)/chipmunk/cpSpace.o \
$(OBJDIR)/chipmunk/cpSpaceHash.o \
$(OBJDIR)/chipmunk/cpVect.o \
\
$(OBJDIR)/Body.o \
$(OBJDIR)/love_chipmunk.o \
$(OBJDIR)/mod_chipmunk.o \
$(OBJDIR)/Shape.o \
$(OBJDIR)/Space.o

CC = g++
CFLAGS = -g -O2 -Wall
LDFLAGS = -llua5.1
INCLUDES = -I/usr/include/lua5.1 -Isrc/liblove/include

default: prep $(TARGET)

$(TARGET): $(OBJ) $(BINDIR)/liblove.a
	$(CC) -shared $(LDFLAGS) -o $(BINDIR)/$@ $^

$(OBJDIR)/chipmunk/%.o: $(SRCDIR)/chipmunk/%.c
	$(CC) -fPIC -g0 -O3 -Wno-conversion $(INCLUDES) -c $< -o $@

$(OBJDIR)/mod_chipmunk.o: $(SRCDIR)/mod_chipmunk.cpp
	$(CC) -fPIC -g0 -O3 $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -fPIC $(CFLAGS) $(INCLUDES) -c $< -o $@

prep:
	mkdir -p obj/chipmunk &> /dev/null

clean:
	rm -f $(OBJ)
