#include "NeoFontTexGame.h"

#include "love.h"
#include "Core.h"
#include "Mouse.h"
#include "AbstractFileSystem.h"
#include "AbstractImageDevice.h"
#include "GameConfiguration.h"
#include "love_keys.h"
#include <vector>
#include "Vector.h"

#include <cmath>

using love::Color;
using love::Vector;
using std::vector;

NeoFontTexGame::NeoFontTexGame()
{
}

NeoFontTexGame::~NeoFontTexGame()
{

}


int NeoFontTexGame::load()
{


	const love::AbstractFileSystem & fs = love::core->getFilesystem();
	const love::AbstractImageDevice & imaging = love::core->getImaging();

	b.reset<Bezier>(new Bezier());
	b->first(0, 0, 50, 200, 200, 200, 400, 100);
	b->next(500, 100, 550, 200, 600, 300);





	// Load image
	img.reset<love::AbstractImage>(imaging.getImage(fs.getBaseFile("data/part1.png")));

	// Get font
	font = new love::Font(fs.getBaseFile("data/fonts/FreeSans.ttf"), 12);

	// Create particle system
	psys = new BezierParticleSystem();
	psys->setBezier(&b);

	psys->setSprite(&img);
	//psys->setParticlesPerSecond(1000);
	psys->addColor(255, 200, 126, 255);
	psys->addColor(255, 0, 126, 0);
	psys->setStartSpeed(0);
	psys->setDirection(0, 360);
	psys->setParticleLifetime(1);
	//psys->setRadialAcc(-300, -400);
	//psys->setTangentialAcc(1000);
	psys->setParticleSize(2, 1);
	psys->setPosition(400, 300);
	//psys->setParticleSpin(90);
	psys->setLifetime(0.4f);
	psys->setSpeed(0.3f);
	psys->setGravity(50, 200);
	psys->setPrecision(300);




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





	inited = true;
	r = 0;

	return love::LOVE_OK;
}

void NeoFontTexGame::render()
{





	// Test render bezier curve.
	/**
	const vector<Vector> points = b->getPoints();

	int num = 50;
	float p = 1.0f/(float)(num-1);

	glDisable(GL_TEXTURE_2D);
	glLineWidth(4);
	glEnable(GL_LINE_SMOOTH);
	glColor4ub(255,255, 255, 255);
	glBegin(GL_LINE_STRIP);

	for(int i = 0;i<num;i++)
	{
		Vector v = b->getPoint(i*p);
		glVertex2f(v.getX(), v.getY());
	}

	glEnd();
	**/


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


		b->setPoint(0, x, y);


		psys->reset();
		break;
	}
}
