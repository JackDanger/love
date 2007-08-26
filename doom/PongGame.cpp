#include "PongGame.h"
#include "Viewport.h"
#include "Point.h"
#include "Vector.h"
#include "Polygon.h"
#include "Window.h"
#include "Core.h"

#include <map>
#include <iterator>
#include <cmath>
#include <ctime>

using std::iterator;



PongGame::PongGame()
{
	srand((unsigned int)time(0));
	setName("ULTRA KILLAH PONG! (Used for testing event system)");
}

PongGame::~PongGame()
{

}

void PongGame::init()
{

	// Players
	vector<Vextor> v;
	v.push_back(Vextor(-10, -40));
	v.push_back(Vextor(-10, 40));
	v.push_back(Vextor(10, 40));
	v.push_back(Vextor(10, -40));

	bodies["player1"] = pBody(new Body(Vextor(20, 325), v, 0.0f));

	v.clear();
	v.push_back(Vextor(-10, -1000));
	v.push_back(Vextor(-10, 1000));
	v.push_back(Vextor(10, 1000));
	v.push_back(Vextor(10, -1000));

	bodies["player2"] = pBody(new Body(Vextor(20, 325), v, 0.0f));


	v.clear();
	v.push_back(Vextor(-10, -10));
	v.push_back(Vextor(-10, 10));
	v.push_back(Vextor(10, 10));
	v.push_back(Vextor(10, -10));

	bodies["ball"] = pBody(new Body(Vextor(20, 325), v, 0.0f));

	// walls
	v.clear();
	v.push_back(Vextor(-600, -10));
	v.push_back(Vextor(-600, 10));
	v.push_back(Vextor(600, 10));
	v.push_back(Vextor(600, -10));

	bodies["wall1"] = pBody(new Body(Vextor(500, 0), v, 0.0));
	bodies["wall2"] = pBody(new Body(Vextor(500, 700), v, 0.0));

	setInited(true);
	// Get collection of bodies

	balldirx = 1;
	balldiry = 1;

	bsx = -200.0f;
	bsy = 0.0f;

	mxl = 0.0f;
	myl = 0.0f;
	mx = 20.0f;
	my = 325.0f;

	font = new Font("Arial", 10);

	setInited(true);
	
}

void PongGame::render()
{

	for(bodies.begin(); !bodies.end(); bodies.next())
		bodies.value()->render();


	glTranslatef(50.0f,50.0f, 0.0f);
	
	font->print("THIS IS TEXT");
}

void PongGame::update(float dt)
{

	

	bodies["player1"]->setPosition(Vextor(bodies["player1"]->getPosition().getX(), this->my));

	bsx *= 0.9999;

	bodies["ball"]->setDisplacement(Vextor(bsx * dt, bsy * dt));



	if(Core::isKeyDown(SDLK_RIGHT))
	{

	}

	if(Core::isKeyDown(SDLK_LEFT))
	{

	}

	if(Core::isKeyDown(SDLK_DOWN))
	{

	}

	if(Core::isKeyDown(SDLK_UP))
	{

	}


	coldet.resolve(*bodies.get(player1), *bodies.get(ball));
	coldet.resolve(*bodies.get(player2), *bodies.get(ball));
	coldet.resolve(*bodies.get(wall1), *bodies.get(ball));
	coldet.resolve(*bodies.get(wall2), *bodies.get(ball));

	for each(pair<int, Body *> p in bodies.getMap())
	{
		p.second->update(dt);
	}

}



void PongGame::keyPressed(int key)
{

}

void PongGame::keyReleased(int key)
{

}

void PongGame::mousePressed(float x, float y)
{

}

void PongGame::mouseReleased(float x, float y)
{

}

void PongGame::mouseMoved(float xlast, float ylast, float x, float y)
{
	mxl = xlast;
	myl = ylast;
	mx = x;
	my = y;
}

void PongGame::eventFired(Event e)
{

	int type = e.getType();

	if( type == Event::LOVE_INIT )
	{
		printf("Event: LOVE_INIT\n");
	}

	if( type == Event::LOVE_COLLIDE )
	{
		const vector<int> & data = e.getData();
		printf("Event: Collision: %i vs %i\n", data[0], data[1]);

		if(data[1] == ball && (data[0] == player1 ||data[0] == player2))
		{
			bsx *= -1.15;
			bsy += (my - myl)/10;
		}

		if(data[1] == ball && (data[0] == wall1 || data[0] == wall2))
		{
			bsy *= -1;
		}

	}

}