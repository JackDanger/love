// File: love.i
%module love

// Include constants
%include love_constants.i

// Ignore things here.
%ignore love::Scriptable;
%ignore love::Loadable;
%ignore love::AbstractEntity;
%ignore love::Entity.h;
%ignore love::VisualEntity.h;
%ignore love::Renderable.h;
%ignore love::Listener.h;
%ignore love::MouseListener.h;
%ignore love::KeyListener.h;

// Do not generate default constructors.
%nodefaultctor;

// Headers
%{

#include "love.h"
#include "lualove_globals.h"

#include "ObjectFactory.h"
#include "AbstractGraphics.h"
#include "AbstractSoundDevice.h"

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
#include "GUIElement.h"
#include "Button.h"
#include "DropDown.h"
#include "Label.h"
#include "MultilineLabel.h"
#include "TextField.h"
#include "RadioButton.h"
#include "CheckBox.h"
#include "Slider.h"
#include "ListBox.h"
#include "TextBox.h"
#include "AbstractMenu.h"
#include "Menu.h"
#include "GUIContainer.h"
#include "AbstractGUI.h"

#include "Bezier.h"

#include "GUIEvent.h"
#include "MessageEvent.h"

using namespace love;


%}

// SWIG needs this to wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}


%include "Updateable.i"

// Big daddy superclass.
%include "Object.i"

// Input devices
%include "Keyboard.i"
%include "Mouse.i"

// Graphics, etc
%include "Sprite.i"
%include "AbstractImage.i"
%include "FrameAnimation.i"
%include "AbstractFont.h"
%include "AbstractColor.h"

// TEST
// Try to extend abstractcolor.
%extend love::AbstractColor {
	void testColor(const boost::shared_ptr<AbstractColor> * color) const
	{
		self->testColor(*color);
	}
}


%include "Padded.h"
%include "GUIElement.h"
%include "Button.h"
%include "DropDown.h"
%include "Label.h"
%include "MultilineLabel.h"
%include "TextField.h"
%include "RadioButton.h"
%include "CheckBox.h"
%include "Slider.h"
%include "ListBox.h"
%include "TextBox.h"
%include "AbstractMenu.h"
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

// Sound
%include "AbstractSound.i"
%include "AbstractMusic.i"
%include "AbstractSoundDevice.i"

%include "ObjectFactory.h"

%include "Event.h"
%include "GUIEvent.h"
%include "MessageEvent.h"

// Holds all the love.-interfaces.
// (love.graphics, love.audio, etc)
%include "lualove_globals.h"

%template(SmartDisplay) boost::shared_ptr<love::AbstractDisplay>;
%template(SmartAbstractColor) boost::shared_ptr<love::AbstractColor>;
// %template(SmartColor) boost::shared_ptr<love::Color>;
%template(SmartAbstractFont) boost::shared_ptr<love::AbstractFont>;
// %template(SmartFont) boost::shared_ptr<love::Font>;
%template(SmartParticleSystem) boost::shared_ptr<love::ParticleSystem>;
%template(SmartBezier) boost::shared_ptr<love::Bezier>;
// GUI stuff
%template(SmartMenu) boost::shared_ptr<love::AbstractMenu>;
%template(SmartLabel) boost::shared_ptr<love::Label>;
%template(SmartMultilineLabel) boost::shared_ptr<love::MultilineLabel>;
%template(SmartButton) boost::shared_ptr<love::Button>;
%template(SmartTextField) boost::shared_ptr<love::TextField>;
%template(SmartDropDown) boost::shared_ptr<love::DropDown>;
%template(SmartRadioButton) boost::shared_ptr<love::RadioButton>;
%template(SmartCheckBox) boost::shared_ptr<love::CheckBox>;
%template(SmartSlider) boost::shared_ptr<love::Slider>;
%template(SmartListBox) boost::shared_ptr<love::ListBox>;
%template(SmartTextBox) boost::shared_ptr<love::TextBox>;
