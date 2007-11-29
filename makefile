CC=g++
CFLAGS=-c -Wall -Wno-unused-label
LDFLAGS=-lGL -lGLU -lIL -lILU -lILUT -lSDL -lSDL_mixer -lSDL_image -llua5.1 -lphysfs -lfreetype -lguichan -lguichan_opengl -lguichan_sdl
DIR=src
SOURCES=AbstractAudio.cpp \
AbstractColor.cpp \
AbstractDevice.cpp \
AbstractDisplay.cpp \
AbstractEntity.cpp \
AbstractFile.cpp \
AbstractFileSystem.cpp \
AbstractFont.cpp \
AbstractGraphics.cpp \
AbstractGUI.cpp \
AbstractImage.cpp \
AbstractImageDevice.cpp \
AbstractMusic.cpp \
AbstractMenu.cpp \
AbstractSound.cpp \
AbstractState.cpp \
AnimatedColor.cpp \
Animation.cpp \
Actor.cpp \
ActorState.cpp \
Bezier.cpp \
BezierParticleSystem.cpp \
Button.cpp \
Color.cpp \
ConfigLoader.cpp \
Container.cpp \
Core.cpp \
CheckBox.cpp \
Display.cpp \
DisplayMode.cpp \
DisplayModeListener.cpp \
DropDown.cpp \
Entity.cpp \
Event.cpp \
EventListener.cpp \
FileSystem.cpp \
FrameAnimation.cpp \
FontTexGame.cpp \
GameConfiguration.cpp \
GameConfigurationLoader.cpp \
GameControlEvent.cpp \
Game.cpp \
GUIElement.cpp \
Globals.cpp \
GUICircleButton.cpp \
GUIDynamicBackground.cpp \
GUIEntity.cpp \
GUIGameList2.cpp \
GUIGameList.cpp \
GUIGameListElement.cpp \
GUIRadialKnob.cpp \
GUIEvent.cpp \
GUIContainer.cpp \
GUIList.cpp \
GUIText.cpp \
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
LuaGL.cpp \
lualove.cpp \
lualove_types_lookup.cpp \
ListBox.cpp \
Label.cpp \
main.cpp \
Matrix.cpp \
Menu.cpp \
MessageEvent.cpp \
Mouse.cpp \
MouseListener.cpp \
MouseMotionListener.cpp \
MultilineLabel.cpp \
NeoFontTexGame.cpp \
Object.cpp \
ObjectFactory.cpp \
OpenGLGraphics.cpp \
OpenGLImage.cpp \
OpenGLFont.cpp \
OpenGLImageFont.cpp \
OpenGLGUI.cpp \
OpenGLParticleSystem.cpp \
Parameters.cpp \
Padded.cpp \
Particle.cpp \
ParticleEmitter.cpp \
ParticleSystem.cpp \
PhysFSFile.cpp \
PhysFSFileSystem.cpp \
platform-sdl.cpp \
Renderable.cpp \
Resource.cpp \
Resumable.cpp \
RadioButton.cpp \
Scriptable.cpp \
ScriptableParticle.cpp \
ScrollMenu.cpp \
SDLDisplay.cpp \
SDLMixerMusic.cpp \
SDLMixerSound.cpp \
SDLMixerAudio.cpp \
SDLTimer.cpp \
SmoothAnimatedColor.cpp \
ScriptableActorState.cpp \
Sprite.cpp \
Slider.cpp \
Text.cpp \
Timer.cpp \
TextBox.cpp \
TextField.cpp \
Updateable.cpp \
UIGame.cpp \
Vector.cpp \
Vextor.cpp \
VisualEntity.cpp \
WindowMenu.cpp
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
