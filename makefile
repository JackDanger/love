CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lGL -lGLU -lIL -lILU -lILUT -lSDL -lSDL_mixer -llua5.1 -lphysfs -lfreetype
DIR=src:/usr/local/lib
SOURCES=AbstractColor.cpp \
AbstractDevice.cpp \
AbstractDisplay.cpp \
AbstractEntity.cpp \
AbstractFile.cpp \
AbstractFileSystem.cpp \
AbstractGraphics.cpp \
AbstractImage.cpp \
AbstractImageDevice.cpp \
AbstractMusic.cpp \
AbstractSound.cpp \
AbstractSoundDevice.cpp \
AbstractState.cpp \
Actor.cpp \
ActorState.cpp \
AnimatedColor.cpp \
Animation.cpp \
Bezier.cpp \
BezierParticleSystem.cpp \
Color.cpp \
ConfigLoader.cpp \
Console.cpp \
Container.cpp \
Core.cpp \
DevILImage.cpp \
DevILImageDevice.cpp \
Display.cpp \
DisplayMode.cpp \
DisplayModeListener.cpp \
Entity.cpp \
Event.cpp \
EventListener.cpp \
FileSystem.cpp \
Font.cpp \
FrameAnimation.cpp \
GameConfiguration.cpp \
GameConfigurationLoader.cpp \
GameControlEvent.cpp \
Game.cpp \
GameObjectContainer.cpp \
GameState.cpp \
Globals.cpp \
GradientColor.cpp \
GUICircleButton.cpp \
GUIDynamicBackground.cpp \
GUIEntity.cpp \
GUIGameList2.cpp \
GUIGameList.cpp \
GUIGameListElement.cpp \
GUIList.cpp \
GUIRadialKnob.cpp \
ImageFromFile.cpp \
Initializable.cpp \
Keyboard.cpp \
KeyListener.cpp \
Listener.cpp \
Loadable.cpp \
Loader.cpp \
LoadListener.cpp \
love_lua_glue.cpp \
LoveMenu4.cpp \
LuaGame.cpp \
LuaGameState.cpp \
LuaGL.cpp \
lualove.cpp \
lualove_types_lookup.cpp \
main.cpp \
Matrix.cpp \
MessageEvent.cpp \
Mouse.cpp \
MouseListener.cpp \
MouseMotionListener.cpp \
NeoFontTexGame.cpp \
Object.cpp \
ObjectFactory.cpp \
OpenGLGraphics.cpp \
Padded.cpp \
Parameters.cpp \
Particle.cpp \
ParticleEmitter.cpp \
ParticleSystem.cpp \
PhysFSFile.cpp \
PhysFSFileSystem.cpp \
platform-sdl.cpp \
Renderable.cpp \
Resource.cpp \
Resumable.cpp \
ScriptableActorState.cpp \
Scriptable.cpp \
ScriptableParticle.cpp \
SDLDisplay.cpp \
SDLMixerMusic.cpp \
SDLMixerSound.cpp \
SDLMixerSoundDevice.cpp \
SDLTimer.cpp \
SmoothAnimatedColor.cpp \
Sprite.cpp \
Text.cpp \
Timer.cpp \
Updateable.cpp \
Vector.cpp \
Vextor.cpp \
VisualEntity.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=love
VPATH=src

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -I/usr/include -I/usr/include/freetype2 -I/usr/include/lua5.1 -I/usr/include/SDL $< -o $@

clean:
	rm -rf src/*o *o love
