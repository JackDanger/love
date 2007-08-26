#include "ChangeGame.h"
#include "Core.h"

#include "lualove.h"

#ifdef __cplusplus
extern "C" 
{

	int extern Love_Init(lua_State * L);
}
#endif

// DevIL
#include <IL/ilut.h>

#include <map>
#include <string>
#include <sstream>

using std::map;
using std::string;
using std::stringstream;
using namespace love;

ChangeGame::ChangeGame()
{
	setTitle("GENERIC TEST SHIT");
}

ChangeGame::~ChangeGame()
{

}

void ChangeGame::init()
{
	actor.reset<Actor>(new Actor());
	sprite.reset<Sprite>(new ImageFromFile("data/kalkun.gif"));
	actor->setSprite(sprite.get());
	load();
	actor->setAcceleration(10.0f, 5.0f);
	setInited(true);
}

void ChangeGame::render()
{
	actor->render();
}

void ChangeGame::update(float dt)
{
	actor->update(dt);
}

void ChangeGame::load()
{
	sprite->load();
}

void ChangeGame::unload()
{
	sprite->unload();
}

