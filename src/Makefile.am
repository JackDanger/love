SUBDIRS =
AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -I/usr/include/freetype2  $(INCLUDE_LUA) -I/usr/include/SDL -Iliblove/include -Ibox2d/Include

# LÖVE executable
bin_PROGRAMS = love
love_LDFLAGS = -lfreetype -lGL -lGLU -lIL -lILU -lILUT -lphysfs -lSDL -lSDL_mixer
love_LDADD =

love_SOURCES = love.cpp \
\
./box2d/graham/GrahamScanConvexHull.cpp \
./box2d/Source/Collision/b2BroadPhase.cpp \
./box2d/Source/Collision/b2CollideCircle.cpp \
./box2d/Source/Collision/b2CollidePoly.cpp \
./box2d/Source/Collision/b2Collision.cpp \
./box2d/Source/Collision/b2Distance.cpp \
./box2d/Source/Collision/b2PairManager.cpp \
./box2d/Source/Collision/b2TimeOfImpact.cpp \
./box2d/Source/Collision/Shapes/b2Shape.cpp \
./box2d/Source/Collision/Shapes/b2CircleShape.cpp \
./box2d/Source/Collision/Shapes/b2PolygonShape.cpp \
./box2d/Source/Common/b2BlockAllocator.cpp \
./box2d/Source/Common/b2Math.cpp \
./box2d/Source/Common/b2Settings.cpp \
./box2d/Source/Common/b2StackAllocator.cpp \
./box2d/Source/Dynamics/b2Body.cpp \
./box2d/Source/Dynamics/b2ContactManager.cpp \
./box2d/Source/Dynamics/b2Island.cpp \
./box2d/Source/Dynamics/b2WorldCallbacks.cpp \
./box2d/Source/Dynamics/b2World.cpp \
./box2d/Source/Dynamics/Contacts/b2CircleContact.cpp \
./box2d/Source/Dynamics/Contacts/b2Contact.cpp \
./box2d/Source/Dynamics/Contacts/b2ContactSolver.cpp \
./box2d/Source/Dynamics/Contacts/b2PolyAndCircleContact.cpp \
./box2d/Source/Dynamics/Contacts/b2PolyContact.cpp \
./box2d/Source/Dynamics/Joints/b2DistanceJoint.cpp \
./box2d/Source/Dynamics/Joints/b2GearJoint.cpp \
./box2d/Source/Dynamics/Joints/b2Joint.cpp \
./box2d/Source/Dynamics/Joints/b2MouseJoint.cpp \
./box2d/Source/Dynamics/Joints/b2PrismaticJoint.cpp \
./box2d/Source/Dynamics/Joints/b2PulleyJoint.cpp \
./box2d/Source/Dynamics/Joints/b2RevoluteJoint.cpp \
./box2d/Body.cpp \
./box2d/CircleShape.cpp \
./box2d/Contact.cpp \
./box2d/DistanceJoint.cpp \
./box2d/Joint.cpp \
./box2d/love_box2d.cpp \
./box2d/mod_box2d.cpp \
./box2d/MouseJoint.cpp \
./box2d/PolygonShape.cpp \
./box2d/PrismaticJoint.cpp \
./box2d/RevoluteJoint.cpp \
./box2d/Shape.cpp \
./box2d/World.cpp \
\
./liblove/arg.cpp \
./liblove/Configuration.cpp \
./liblove/Core.cpp \
./liblove/DynamicModule.cpp \
./liblove/Exception.cpp \
./liblove/File.cpp \
./liblove/Game.cpp \
./liblove/include/love/arg.h \
./liblove/include/love/Configuration.h \
./liblove/include/love/constants.h \
./liblove/include/love/Core.h \
./liblove/include/love/DynamicModule.h \
./liblove/include/love/events.h \
./liblove/include/love/Exception.h \
./liblove/include/love/File.h \
./liblove/include/love/Game.h \
./liblove/include/love/luax.h \
./liblove/include/love/math.h \
./liblove/include/love/MemoryFile.h \
./liblove/include/love/mod.h \
./liblove/include/love/modspec.h \
./liblove/include/love/Module.h \
./liblove/include/love/platform.h \
./liblove/include/love/Reference.h \
./liblove/include/love/Resource.h \
./liblove/include/love/StaticModule.h \
./liblove/include/love/Vector.h \
./liblove/include/love/version.h \
./liblove/luax.cpp \
./liblove/MemoryFile.cpp \
./liblove/modspec.cpp \
./liblove/Module.cpp \
./liblove/Reference.cpp \
./liblove/Resource.cpp \
./liblove/StaticModule.cpp \
./liblove/Vector.cpp \
./liblove/version.cpp \
\
./luasocket/luasocket/auxiliar.h \
./luasocket/luasocket/inet.h \
./luasocket/luasocket/mime.h \
./luasocket/luasocket/socket.h \
./luasocket/luasocket/udp.h \
./luasocket/luasocket/buffer.h \
./luasocket/luasocket/io.h \
./luasocket/luasocket/options.h \
./luasocket/luasocket/tcp.h \
./luasocket/luasocket/unix.h \
./luasocket/luasocket/except.h \
./luasocket/luasocket/luasocket.h \
./luasocket/luasocket/select.h \
./luasocket/luasocket/timeout.h \
./luasocket/luasocket/usocket.h \
./luasocket/luasocket/auxiliar.c \
./luasocket/luasocket/luasocket.c \
./luasocket/luasocket/select.c \
./luasocket/luasocket/timeout.c \
./luasocket/luasocket/buffer.c \
./luasocket/luasocket/inet.c \
./luasocket/luasocket/mime.c \
./luasocket/luasocket/usocket.c \
./luasocket/luasocket/except.c \
./luasocket/luasocket/io.c \
./luasocket/luasocket/udp.c \
./luasocket/luasocket/options.c \
./luasocket/luasocket/tcp.c \
./luasocket/luasocket/unix.c \
./luasocket/love_luasocket.h \
./luasocket/love_luasocket.cpp \
\
./opengl/love_opengl.cpp \
./opengl/Animation.cpp \
./opengl/Animation.h \
./opengl/Color.cpp \
./opengl/Color.h \
./opengl/Font.cpp \
./opengl/Font.h \
./opengl/GLee.c \
./opengl/GLee.h \
./opengl/Image.cpp \
./opengl/Image.h \
./opengl/ImageFont.cpp \
./opengl/ImageFont.h \
./opengl/love_opengl.h \
./opengl/mod_opengl.cpp \
./opengl/mod_opengl.h \
./opengl/ParticleSystem.cpp \
./opengl/ParticleSystem.h \
./opengl/PointParticleSystem.cpp \
./opengl/PointParticleSystem.h \
./opengl/resources.cpp \
./opengl/resources.h \
./opengl/Sprite.cpp \
./opengl/Sprite.h \
./opengl/TrueTypeFont.cpp \
./opengl/TrueTypeFont.h \
./opengl/Volatile.cpp \
./opengl/Volatile.h \
\
./physfs/File.cpp \
./physfs/File.h \
./physfs/love_physfs.cpp \
./physfs/love_physfs.h \
./physfs/mod_physfs.cpp \
./physfs/mod_physfs.h \
\
./sdlkeyboard/love_sdlkeyboard.cpp \
./sdlkeyboard/love_sdlkeyboard.h \
./sdlkeyboard/mod_sdlkeyboard.cpp \
./sdlkeyboard/mod_sdlkeyboard.h \
\
./sdlmixer/love_sdlmixer.cpp \
./sdlmixer/love_sdlmixer.h \
./sdlmixer/mod_sdlmixer.cpp \
./sdlmixer/mod_sdlmixer.h \
./sdlmixer/Music.cpp \
./sdlmixer/Music.h \
./sdlmixer/Sound.cpp \
./sdlmixer/Sound.h \
\
./sdlmouse/love_sdlmouse.cpp \
./sdlmouse/love_sdlmouse.h \
./sdlmouse/mod_sdlmouse.cpp \
./sdlmouse/mod_sdlmouse.h \
\
./sdljoystick/love_sdljoystick.cpp \
./sdljoystick/love_sdljoystick.h \
./sdljoystick/mod_sdljoystick.cpp \
./sdljoystick/mod_sdljoystick.h \
\
./sdltimer/love_sdltimer.cpp \
./sdltimer/love_sdltimer.h \
./sdltimer/mod_sdltimer.cpp \
./sdltimer/mod_sdltimer.h \
\
./system/love_system.cpp \
./system/love_system.h \
./system/LuaGame.cpp \
./system/LuaGame.h \
./system/mod_system.cpp \
./system/mod_system.h \
./system/resources.cpp \
./system/resources.h \
./system/constants.h
