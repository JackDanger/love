#include "Actor.h"
#include "love.h"

namespace love
{
	Actor::Actor()
	{
		this->sprites = 0;
		currentState = new ActorState(this);
		states.create("default", currentState);
		setType(LOVE_TYPE_ACTOR);
	}

	/*Actor::Actor(lua_State * L, Container<Sprite> * sprites)
	{
		this->L = L;
		this->sprites = sprites;
		currentState = new ActorState(this);
		states.create("default", currentState);
		setType(LOVE_TYPE_ACTOR);
	}*/

	Actor::Actor(lua_State * L, Container<Sprite> * sprites, const char * scriptname)
	{
		this->L = L;
		this->sprites = sprites;
		ActorState * temp;
		if(scriptname == "")
			temp = new ActorState(this);
		else
			temp = new ScriptableActorState(this, L, scriptname);
		states.create("default", temp);
		currentState = temp;
		setType(LOVE_TYPE_ACTOR);
	}

	Actor::~Actor()
	{ }

	ActorState * Actor::addState(const char * name)
	{
		ActorState * temp = new ActorState(this);
		states.create(name, temp);
		return temp;
	}

	ActorState * Actor::addState(const char * name, const char * scriptname)
	{
		states.create(name, new ScriptableActorState(this, L, scriptname));
		return states[name].get();
	}

	ActorState * Actor::getState(const char * name)
	{
		return states[name].get();
	}

	void Actor::setState(const char * name)
	{
		currentState = states[name].get();
	}

	void Actor::setState(ActorState * newState)
	{
		currentState = newState;
	}

	Sprite* Actor::getSprite(const char * name)
	{
		if(sprites != 0)
			return (*sprites)[name].get();
		else
			return 0;
	}

	//ActorState functions

	float Actor::getX() { return currentState->getX(); }
	float Actor::getY() { return currentState->getY(); }
	float Actor::getZ() { return currentState->getZ(); }
	void Actor::setX(float x) { currentState->setX(x); }
	void Actor::setY(float y) { currentState->setY(y); }
	void Actor::setZ(float z) { currentState->setZ(z); }
	Vector* Actor::getPosition() { return currentState->getPosition(); }
	float Actor::getXPosition() { return currentState->getXPosition(); }
	float Actor::getYPosition() { return currentState->getYPosition(); }
	float Actor::getZPosition() { return currentState->getZPosition(); }
	void Actor::setPosition(Vector * newPosition) { currentState->setPosition(newPosition); }
	void Actor::setPosition(float x, float y) { currentState->setPosition(x,y); }
	void Actor::setXPosition(float x) { currentState->setXPosition(x); }
	void Actor::setYPosition(float y) { currentState->setYPosition(y); }
	void Actor::setZPosition(float z) { currentState->setZPosition(z); }
	Vector* Actor::getVelocity() { return currentState->getVelocity(); }
	float Actor::getXVelocity() { return currentState->getXVelocity(); }
	float Actor::getYVelocity() { return currentState->getYVelocity(); }
	void Actor::setVelocity(Vector * newVelocity) { currentState->setVelocity(newVelocity); }
	void Actor::setVelocity(float x, float y) { currentState->setVelocity(x,y); }
	void Actor::setXVelocity(float x) { currentState->setXVelocity(x); }
	void Actor::setYVelocity(float y) { currentState->setYVelocity(y); }
	Vector* Actor::getAcceleration() { return currentState->getAcceleration(); }
	float Actor::getXAcceleration() { return currentState->getXAcceleration(); }
	float Actor::getYAcceleration() { return currentState->getYAcceleration(); }
	void Actor::setAcceleration(Vector * newAcceleration) { currentState->setAcceleration(newAcceleration); }
	void Actor::setAcceleration(float x, float y) { currentState->setAcceleration(x,y); }
	void Actor::setXAcceleration(float x) { currentState->setXAcceleration(x); }
	void Actor::setYAcceleration(float y) { currentState->setYAcceleration(y); }
	float Actor::getOrientation() { return currentState->getOrientation(); }
	void Actor::setOrientation(float orientation) { currentState->setOrientation(orientation); }
	Sprite* Actor::getSprite() { return currentState->getSprite(); }
	void Actor::setSprite(const char * name) { if(sprites != 0) currentState->setSprite((*sprites)[name].get()); }
	void Actor::setSprite(Sprite * sprite) { currentState->setSprite(sprite); }


	void Actor::update(float dt) { currentState->update(dt); }
	void Actor::render() { currentState->render(); }

	void Actor::init()
	{
		// Init states
		for(states.begin(); !states.end(); states.next())
			states.value()->init();
	}

	int Actor::load()
	{
		// Load states
		for(states.begin(); !states.end(); states.next())
			states.value()->load();

		return LOVE_OK;
	}

	void Actor::unload()
	{
	}
}
