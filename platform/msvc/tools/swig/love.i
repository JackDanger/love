/* File : love.i */
%module love

// Include constants
%include love_constants.i

// Ignore different things here.
%ignore love::Scriptable;

%{

#include "love.h"
#include "lualove_globals.h"

#include "ObjectFactory.h"
#include "AbstractGraphics.h"

#include "AbstractState.h"
#include "ActorState.h"
#include "ScriptableActorState.h"
#include "Actor.h"

#include "Particle.h"
#include "ScriptableParticle.h"
#include "ParticleEmitter.h"

#include "AbstractColor.h"
#include "Color.h"
#include "AnimatedColor.h"
#include "AbstractFont.h"
#include "Font.h"
#include "ImageFont.h"
#include "Text.h"

#include "love_globals.h"
#include "Container.h"
#include "Object.h"
#include "Vector.h"
#include "Listener.h"
#include "MouseListener.h"
#include "KeyListener.h"
#include "Updateable.h"
#include "Renderable.h"
#include "AbstractEntity.h"
#include "Entity.h"
#include "VisualEntity.h"
#include "ParticleSystem.h"

#include "AbstractSound.h"
#include "AbstractMusic.h"
#include "AbstractDisplay.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "Game.h"
#include "LuaGame.h"
#include "Timer.h"
#include "DisplayMode.h"
#include "LuaGL.h"

#include "AbstractImage.h"
#include "FrameAnimation.h"

#include "Padded.h"
#include "Button.h"
#include "DropDown.h"
#include "Label.h"
#include "MultilineLabel.h"
#include "TextField.h"
#include "RadioButton.h"
#include "Menu.h"
#include "GUIContainer.h"
#include "AbstractGUI.h"

#include "Bezier.h"

#include "GUIEvent.h"
#include "MessageEvent.h"

using namespace love;


%}

namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

// Interfaces here plx.
%include "Updateable.h"
%include "Renderable.h"
%include "Loadable.h"
%include "Listener.h"
%include "MouseListener.h"
%include "KeyListener.h"

%include "love_globals.h"
%include "Container.h"
%include "Object.h"
%include "Vector.h"



%include "AbstractColor.h"
%include "Color.h"

%include "AbstractFont.h"
%include "Font.h"
%include "Text.h"

%include "Keyboard.h"
%include "Mouse.h"


%include "AbstractEntity.h"


%include "Entity.h"
%include "VisualEntity.h"


%include "AbstractSound.h"
%include "AbstractMusic.h"

%include "AbstractState.h"
%include "ActorState.h"
%include "Actor.h"

%include "Sprite.h"
%include "AbstractImage.h"
%include "FrameAnimation.h"
%include "Bezier.h"

%include "Padded.h"
%include "Button.h"
%include "DropDown.h"
%include "Label.h"
%include "MultilineLabel.h"
%include "TextField.h"
%include "RadioButton.h"
%include "Menu.h"
%include "GUIContainer.h"
%include "AbstractGUI.h"

%include "ParticleSystem.h"

%include "Timer.h"
%include "DisplayMode.h"
%include "LuaGL.h"

%include "LuaGame.h"

%include "AbstractDisplay.h"
%include "AbstractGraphics.h"

%include "ObjectFactory.h"

%include "Event.h"
%include "GUIEvent.h"
%include "MessageEvent.h"

%include "lualove_globals.h"



%ignore love::pAbstractImage;

%template(SmartSprite) boost::shared_ptr<love::Sprite>;
%template(SmartImage) boost::shared_ptr<love::AbstractImage>;
%template(SmartAnimation) boost::shared_ptr<love::FrameAnimation>;
%template(SmartMusic) boost::shared_ptr<love::AbstractMusic>;
%template(SmartSound) boost::shared_ptr<love::AbstractSound>;
%template(SmartDisplay) boost::shared_ptr<love::AbstractDisplay>;
%template(SmartAbstractColor) boost::shared_ptr<love::AbstractColor>;
%template(SmartColor) boost::shared_ptr<love::Color>;
%template(SmartAbstractFont) boost::shared_ptr<love::AbstractFont>;
%template(SmartFont) boost::shared_ptr<love::Font>;
%template(SmartParticleSystem) boost::shared_ptr<love::ParticleSystem>;
%template(SmartBezier) boost::shared_ptr<love::Bezier>;
%template(SmartMenu) boost::shared_ptr<love::Menu>;