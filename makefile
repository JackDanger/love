TARGET = love
BINDIR = .
OBJDIR = platform/unix
SRCDIR = src
OBJ = $(OBJDIR)/AbstractAudio.o \
$(OBJDIR)/AbstractColor.o \
$(OBJDIR)/AbstractDevice.o \
$(OBJDIR)/AbstractDisplay.o \
$(OBJDIR)/AbstractEntity.o \
$(OBJDIR)/AbstractFile.o \
$(OBJDIR)/AbstractFileSystem.o \
$(OBJDIR)/AbstractFont.o \
$(OBJDIR)/AbstractGraphics.o \
$(OBJDIR)/AbstractGUI.o \
$(OBJDIR)/AbstractImage.o \
$(OBJDIR)/AbstractImageDevice.o \
$(OBJDIR)/AbstractMusic.o \
$(OBJDIR)/AbstractMenu.o \
$(OBJDIR)/AbstractSound.o \
$(OBJDIR)/AbstractState.o \
$(OBJDIR)/AnimatedColor.o \
$(OBJDIR)/Animation.o \
$(OBJDIR)/Actor.o \
$(OBJDIR)/ActorState.o \
$(OBJDIR)/Bezier.o \
$(OBJDIR)/BezierParticleSystem.o \
$(OBJDIR)/Button.o \
$(OBJDIR)/Color.o \
$(OBJDIR)/ConfigLoader.o \
$(OBJDIR)/Container.o \
$(OBJDIR)/Core.o \
$(OBJDIR)/CheckBox.o \
$(OBJDIR)/Display.o \
$(OBJDIR)/DisplayMode.o \
$(OBJDIR)/DisplayModeListener.o \
$(OBJDIR)/DropDown.o \
$(OBJDIR)/Entity.o \
$(OBJDIR)/Event.o \
$(OBJDIR)/EventListener.o \
$(OBJDIR)/FileSystem.o \
$(OBJDIR)/FrameAnimation.o \
$(OBJDIR)/FontTexGame.o \
$(OBJDIR)/GameConfiguration.o \
$(OBJDIR)/GameConfigurationLoader.o \
$(OBJDIR)/GameControlEvent.o \
$(OBJDIR)/Game.o \
$(OBJDIR)/GUIElement.o \
$(OBJDIR)/Globals.o \
$(OBJDIR)/GUICircleButton.o \
$(OBJDIR)/GUIDynamicBackground.o \
$(OBJDIR)/GUIEntity.o \
$(OBJDIR)/GUIGameList2.o \
$(OBJDIR)/GUIGameList.o \
$(OBJDIR)/GUIGameListElement.o \
$(OBJDIR)/GUIRadialKnob.o \
$(OBJDIR)/GUIEvent.o \
$(OBJDIR)/GUIContainer.o \
$(OBJDIR)/GUIList.o \
$(OBJDIR)/GUIText.o \
$(OBJDIR)/Initializable.o \
$(OBJDIR)/Keyboard.o \
$(OBJDIR)/KeyListener.o \
$(OBJDIR)/Listener.o \
$(OBJDIR)/Loadable.o \
$(OBJDIR)/Loader.o \
$(OBJDIR)/LoadListener.o \
$(OBJDIR)/love_lua_glue.o \
$(OBJDIR)/LoveMenu4.o \
$(OBJDIR)/LuaGame.o \
$(OBJDIR)/LuaGL.o \
$(OBJDIR)/lualove.o \
$(OBJDIR)/lualove_types_lookup.o \
$(OBJDIR)/ListBox.o \
$(OBJDIR)/Label.o \
$(OBJDIR)/main.o \
$(OBJDIR)/Matrix.o \
$(OBJDIR)/Menu.o \
$(OBJDIR)/MessageEvent.o \
$(OBJDIR)/Mouse.o \
$(OBJDIR)/MouseListener.o \
$(OBJDIR)/MouseMotionListener.o \
$(OBJDIR)/MultilineLabel.o \
$(OBJDIR)/NeoFontTexGame.o \
$(OBJDIR)/Object.o \
$(OBJDIR)/ObjectFactory.o \
$(OBJDIR)/OpenGLGraphics.o \
$(OBJDIR)/OpenGLImage.o \
$(OBJDIR)/OpenGLFont.o \
$(OBJDIR)/OpenGLImageFont.o \
$(OBJDIR)/OpenGLGUI.o \
$(OBJDIR)/OpenGLParticleSystem.o \
$(OBJDIR)/Parameters.o \
$(OBJDIR)/Padded.o \
$(OBJDIR)/Particle.o \
$(OBJDIR)/ParticleEmitter.o \
$(OBJDIR)/ParticleSystem.o \
$(OBJDIR)/PhysFSFile.o \
$(OBJDIR)/PhysFSFileSystem.o \
$(OBJDIR)/platform-sdl.o \
$(OBJDIR)/Renderable.o \
$(OBJDIR)/Resource.o \
$(OBJDIR)/Resumable.o \
$(OBJDIR)/RadioButton.o \
$(OBJDIR)/Scriptable.o \
$(OBJDIR)/ScriptableParticle.o \
$(OBJDIR)/ScrollMenu.o \
$(OBJDIR)/SDLDisplay.o \
$(OBJDIR)/SDLMixerMusic.o \
$(OBJDIR)/SDLMixerSound.o \
$(OBJDIR)/SDLMixerAudio.o \
$(OBJDIR)/SDLTimer.o \
$(OBJDIR)/SmoothAnimatedColor.o \
$(OBJDIR)/ScriptableActorState.o \
$(OBJDIR)/Sprite.o \
$(OBJDIR)/Slider.o \
$(OBJDIR)/Text.o \
$(OBJDIR)/Timer.o \
$(OBJDIR)/TextBox.o \
$(OBJDIR)/TextField.o \
$(OBJDIR)/Updateable.o \
$(OBJDIR)/UIGame.o \
$(OBJDIR)/Vector.o \
$(OBJDIR)/Vextor.o \
$(OBJDIR)/VisualEntity.o \
$(OBJDIR)/WindowMenu.o

CC = g++
CFLAGS = -g -O2 -Wall -Wno-unused-label -fno-strict-aliasing
LDFLAGS = -lGL -lGLU -lIL -lILU -lILUT -lSDL -lSDL_mixer -lSDL_image -llua5.1 -lphysfs -lfreetype -lguichan -lguichan_opengl -lguichan_sdl
INCLUDES = -I/usr/include/freetype2 -I/usr/include/lua5.1 -I/usr/include/SDL

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(TARGET)

