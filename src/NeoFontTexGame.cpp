#include "NeoFontTexGame.h"

#include "love.h"
#include "Core.h"
#include "Mouse.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "GameConfiguration.h"
#include "love_keys.h"

#include <cmath>

using love::Color;

NeoFontTexGame::NeoFontTexGame()
{
}

NeoFontTexGame::~NeoFontTexGame()
{

}


int NeoFontTexGame::load()
{


	config->load();
	img->load();
	font->load();
	psys->load();


	loaded = true;
	return love::LOVE_OK;
}

void NeoFontTexGame::unload()
{
	config->unload();
	psys->unload();
	img->unload();
	loaded = false;
}

void NeoFontTexGame::reloadGraphics()
{
	img->load();
}


int NeoFontTexGame::init()
{

	const love::AbstractFileSystem & fs = love::core->getFilesystem();
	const love::AbstractImageDevice & imaging = love::core->getImaging();

	// Create game configuration
	config = new love::GameConfiguration();
	config->setTitle("Neo Font Tex Game");
	config->setAuthor("Grammaton Cleric Preston");

	// Load image
	img = imaging.getImage(fs.getBaseFile("data/part1.png"));

	// Get font
	font = new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 12);

	// Create particle system
	psys = new love::ParticleSystem();

	psys->setSprite(img);
	psys->setParticlesPerSecond(2000);
	psys->addColor(255, 255, 255, 255);
	psys->addColor(255, 0, 126, 0);
	psys->setStartSpeed(300, 400);
	psys->setDirection(0, 360);
	psys->setParticleLifetime(1);
	psys->setRadialAcc(-300, -400);
	psys->setTangentialAcc(1000);
	psys->setParticleSize(1, 2);
	psys->setPosition(400, 300);
	psys->setParticleSpin(90);
	psys->setLifetime(0.1f);
	//psys->setGravity(50, 200);



	inited = true;
	r = 0;

	return love::LOVE_OK;
}

void NeoFontTexGame::render()
{
	psys->render();
}

void NeoFontTexGame::update(float dt)
{

	// Update color
	//clr->update(dt);

	r += 60 * dt;

	
	float x = cos(r) * 100;
	float y = sin(r) * 100;

	const love::Mouse & mouse = love::core->getMouse();

	//psys->setPosition(200,50);
	//psys->setPosition(500 + x, 300 + y);
	psys->setPosition(mouse.getX(), mouse.getY());
	//psys->setDirection(r);
	//psys->setSpread(r);


	psys->update(dt);
}

void NeoFontTexGame::keyPressed(int key)
{
	switch(key)
	{
	case love::LOVE_KEY_RETURN:
		psys->reset();
		break;
	}
}

void NeoFontTexGame::mousePressed(float x, float y, int button)
{
	switch(button)
	{
	case love::LOVE_MOUSE_LEFT:
		psys->reset();
		break;
	}
}
