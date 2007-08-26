#include "DemoGame.h"
#include "Viewport.h"
#include "Point.h"
#include "Vector.h"
#include "Polygon.h"
#include "Window.h"
#include "Core.h"

#include <map>
#include <iterator>
#include <cmath>

using std::iterator;

DemoGame::DemoGame()
{
	srand(time(0));

}

DemoGame::~DemoGame()
{

}

void DemoGame::init()
{
	// Create and load Map
	currentMap = new Map();
	currentMap->load("data/fist4.tmx", Map::FORMAT_TILED);


	// Text system
	textman = new Font("Arial", 26);

	pam = new ParticleEmitter(150,100, "data/blue.png");
	pam->setDirection(0, 15);
	pam->setAmmo(3, 0.016f);
	pam->setVelocity(200, 0);
	pam->setLifetime(10);
	pam->setFade(true);
	pam->setRotation(0.0f, 0.0f);
	pam->start();

	attractors.push_back(Attractor(500, 200, pam, 300, 40));
	attractors.push_back(Attractor(700, 400, pam, 300, 40));
	attractors.push_back(Attractor(900, 200, pam, 250, 100));
	attractors.push_back(Attractor(500, 400, pam, 200, 30));



	camera_x = 1024/2 + 100;
	camera_y = 768/2 + 100;

	setInited(true);
	

}

void DemoGame::render()
{
	

	// Render map.
	currentMap->render();

	// Render particle emitter
	glLoadIdentity();
	currentMap->getViewport()->translate();

	pam->render();

	for(int i=0;i<attractors.size();i++)
		attractors[i].render();


}

void DemoGame::update(float dt)
{

	float speed = 512.0f * dt;

	if(Core::getKeyboard()->isKeyDown(SDLK_RIGHT))
	{
		camera_x += speed;
	}

	if(Core::getKeyboard()->isKeyDown(SDLK_LEFT))
	{
		camera_x -= speed;
	}

	if(Core::getKeyboard()->isKeyDown(SDLK_DOWN))
	{
		camera_y += speed;

	}

	if(Core::getKeyboard()->isKeyDown(SDLK_UP))
	{
		camera_y -= speed;

	}


	// Update map
	currentMap->update(dt);

	// Update particle emitter
	pam->update(dt);

	// Update the attractor
	for(int i=0;i<attractors.size();i++)
		attractors[i].update(dt);

	// Look at the player position.
	currentMap->getViewport()->lookAt(camera_x,camera_y);

}



void DemoGame::keyPressed(int key)
{


	if(key==VK_RETURN)
	{
	}else if(key==SDLK_t){
	}else if(key==SDLK_g){
	}else if(key==SDLK_s){
	}else if(key==SDLK_r){

		pam->doRender = pam->doRender ? false : true;

		for(int i=0;i<attractors.size();i++)
			attractors[i].doRender = attractors[i].doRender ? false : true;

	}else if(key==SDLK_p){
	}else if(key == SDLK_KP_PLUS){
	}else if(key == SDLK_KP_MINUS){
	}
}

void DemoGame::keyReleased(int key)
{

}

void DemoGame::mousePressed(float x, float y, int state)
{
	
}

void DemoGame::mouseReleased(float x, float y, int state)
{

}

void DemoGame::mouseMoved(float x, float y)
{
	pam->setPosition(x + currentMap->getViewport()->getX(), y + currentMap->getViewport()->getY());
}
