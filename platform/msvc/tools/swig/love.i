/* File : love.i */
%module love

// Ignore different things here.
%ignore love::Scriptable;

%{

#include "love.h"

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
#include "Font.h"
#include "Text.h"

#include "love_globals.h"
#include "Container.h"
#include "Object.h"
#include "Vextor.h"
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

#include "Keyboard.h"
#include "Mouse.h"

#include "Game.h"
#include "LuaGame.h"
#include "Timer.h"
#include "DisplayMode.h"
#include "LuaGL.h"

#include "AbstractImage.h"
#include "FrameAnimation.h"

using namespace love;


%}





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
%include "Vextor.h"



%include "AbstractColor.h"
%include "Font.h"
%include "Text.h"

%include "Keyboard.h"
%include "Mouse.h"


%include "AbstractEntity.h"

%include "Sprite.h"
%include "Entity.h"
%include "VisualEntity.h"
%include "ParticleSystem.h"

%include "AbstractSound.h"
%include "AbstractMusic.h"

%include "AbstractState.h"
%include "ActorState.h"
%include "Actor.h"

%include "Particle.h"
%include "ScriptableParticle.h"
%include "ParticleEmitter.h"

%include "ScriptableActorState.h"

%include "AbstractImage.h"
%include "FrameAnimation.h"

%include "Timer.h"
%include "DisplayMode.h"
%include "LuaGL.h"
%include "LuaGame.h"
