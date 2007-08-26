#include "CollisionGame.h"
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

int CollisionGame::playerId = 0;

CollisionGame::CollisionGame()
{
	srand((unsigned int)time(0));
	setName("Collision Detection");
}

CollisionGame::~CollisionGame()
{

}

Body * CollisionGame::createBody3p(Vextor position, Vextor p1, Vextor p2, Vextor p3, float mass)
{
	vector<Vextor> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);

	return new Body(position, v, mass);

}

Body * CollisionGame::createBody4p(Vextor position, Vextor p1, Vextor p2, Vextor p3, Vextor p4, float mass)
{
	vector<Vextor> v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);

	return new Body(position, v, mass);
}

void CollisionGame::init()
{


	forces = true;

	// Load splash screen
	ss = new SplashScreen("data/logo_1024x800.png", 3);


	// Create and load Map
	currentMap = new Map();
	currentMap->load("data/fist4.tmx", Map::FORMAT_TILED);

	useSpatialPartitioning = true;




	/**
	* Body section
	**/

	// Create and add player
	player = createBody4p(Vextor(500,500),Vextor(-25,-40), Vextor(-25,40), Vextor(25,40), Vextor(25,-40),1.0);
	CollisionGame::playerId = player->getId();
	bodies.add(player);

	// Create dynamic bodies
	bodies.add(createBody4p(Vextor(50, 50), Vextor(-25, -25), Vextor(-25, 25), Vextor(25, 25), Vextor(25, -25), 0.7f));
	bodies.add(createBody4p(Vextor(100, 70), Vextor(-25, -25), Vextor(-25, 25), Vextor(25, 25), Vextor(25, -25), 0.7f));
	bodies.add(createBody3p(Vextor(200, -300), Vextor(-25, -25), Vextor(-50, 50), Vextor(50, 50), 0.7f));


	// More dynamic bodies
	for(int i = 0;i<5;i++)
	{
		float x = (float)(rand() % 3900) + 100.0f;
		float y = 200.0f;
		float mass = 0.7;



		bodies.add(createBody4p(Vextor(x, y), Vextor(-25, -25), Vextor(-25, 25), Vextor(25, 25), Vextor(25, -25), mass));
	}



	//bodies.add(createBody4p(Vextor(1500, 400),Vextor(-200, -200),Vextor(-200, 200), Vextor(200, 200), Vextor(200, -200),0.7));



	// Add walls (inverse mass 0)
	bodies.add(createBody4p(Vextor(-230,400),Vextor(-250,-1000), Vextor(-250,1000), Vextor(250,1000), Vextor(250,-1000),0));
	bodies.add(createBody4p(Vextor(1200,400),Vextor(-250,-1000), Vextor(-250,1000), Vextor(250,1000), Vextor(250,-1000),0));
	bodies.add(createBody4p(Vextor(512,-230 - 5000),Vextor(-2000,-250), Vextor(-2000,250), Vextor(2000,250), Vextor(2000,-250),0));
	bodies.add(createBody4p(Vextor(512,950  - 5000),Vextor(-2000,-250), Vextor(-2000,250), Vextor(2000,250), Vextor(2000,-250),0));
	bodies.add(createBody4p(Vextor(300,600),Vextor(-50,-20), Vextor(-50,20), Vextor(50,20), Vextor(50,-20),0));
	bodies.add(createBody4p(Vextor(700,600),Vextor(-50,-20), Vextor(-50,20), Vextor(50,20), Vextor(50,-20),0));
	bodies.add(createBody3p(Vextor(300,100),Vextor(-100,-50),Vextor(0,40), Vextor(100,0),0));
	bodies.add(createBody3p(Vextor(650,300),Vextor(-100,-50),Vextor(100,20), Vextor(100,-100),0));
	
	bodies.add(createBody3p(Vextor(512, 1900),Vextor(-500, -400),Vextor(-500, 400), Vextor(500, 400),0));

	bodies.add(createBody4p(Vextor(2000, 1600),Vextor(-500, -300),Vextor(-500, -280), Vextor(500, 300), Vextor(500, 280),0));





	bodies.add(createBody4p(Vextor(3500, 1900),Vextor(500,-300), Vextor(-500,280), Vextor(-500,300), Vextor(500,-280),0));

	// Create HGrid
	hgrid = new HierarchyGrid(128, 32, 6);

	// Insert static bodies
	for each(pair<int, Body *> b in bodies.getMap())
	{
		if(b.second->getInverseMass() == 0)
			hgrid->insert(b.second);
	}


	// Fire Event for test purposes
	Event e;
	e.setType(Event::LOVE_INIT);

	Core::eventFired(e);

	setInited(true);
	// Get collection of bodies

}

void CollisionGame::render()
{
	

	if(!ss->waiting())
	{

		// Render map.
		currentMap->render();

		// Translate to the current viewport
		currentMap->getViewport()->translate();

		// Render bodies
		const std::map<int,Body *> & bmap = bodies.getMap();
		std::map<int,Body *>::const_iterator iter = bmap.begin();

		while(iter != bmap.end())
		{
			iter->second->render();
			iter++;
		}


		// Render the hierarchy grid for debug purposes
		hgrid->render();

	}

	// Check if splashscreen is done
	if(!ss->isDone())
	{
		ss->render();
	}

}

void CollisionGame::update(float dt)
{


	


	// Check if splash screen is done
	if(!ss->isDone())
	{
		ss->update(dt);

		if(ss->waiting())
			return;
	}


	float f = 1024.0f;

	if(Core::isKeyDown(SDLK_RIGHT))
	{
		player->addImpulse(Vextor(f,0),dt);
	}

	if(Core::isKeyDown(SDLK_LEFT))
	{
		player->addImpulse(Vextor(-f,0),dt);
	}

	if(Core::isKeyDown(SDLK_DOWN))
	{
		player->addImpulse(Vextor(0,f),dt);
	}

	if(Core::isKeyDown(SDLK_UP))
	{
		player->addImpulse(Vextor(0,-f),dt);
	}


	Body * bp = (Body *)player;

	//hgrid->color(bp->getPosition().getX(), bp->getPosition().getY());


	// Update map
	currentMap->update(dt);


	// Get collection of bodies
	const std::map<int,Body *> & bmap = bodies.getMap();
	std::map<int,Body *>::const_iterator iter = bmap.begin();

	// Add forces
	if(forces)
	{
		iter = bmap.begin();
		while(iter != bmap.end())
		{
			iter->second->addImpulse(Vextor(0,200.0f * iter->second->getInverseMass()), dt);
			iter++;
		}
	}
	
	// Insert elements into grid here (after impulses has been applied)

	// Check collision III
	// 
	// for every element a, b
	//	if()
	//
	//
	//
	//

	// Check collisions II

	if(useSpatialPartitioning)
	{


		iter = bmap.begin();
		while(iter != bmap.end())
		{


			if(iter->second->getInverseMass() != 0)
			{
				hgrid->remove(iter->second);
				hgrid->insert(iter->second);
			}

			iter++;
		}

		coldet.resolve(bodies);

	}else
	{


		// Check collisions I
		iter = bmap.begin();
		while(iter != bmap.end())
		{
			std::map<int,Body *>::const_iterator iter2 = iter;
			iter2++;

			while(iter2 != bmap.end())
			{

				coldet.intersects(*iter->second,*iter2->second); 
				iter2++;
			}


			iter++;
		}

	}// if/else

	
	int rc = 128 * 32;
	

	// Update and check position.
	iter = bmap.begin();
	while(iter != bmap.end())
	{
		if(iter->second->getPosition().getY() > rc && iter->second->isMovable())
		{
				iter->second->setPosition(Vextor((float)(rand() % (rc - 100)) + 100, 200));
				iter->second->setDisplacement(Vextor(0,0));
		}

		iter->second->update(dt);

		iter++;
	}


	// Look at the player position.
	currentMap->getViewport()->lookAt(player->getPosition().getX(), player->getPosition().getY());

}



void CollisionGame::keyPressed(int key)
{


	const std::map<int,Body *> & bmap = bodies.getMap();
	std::map<int,Body *>::const_iterator iter = bmap.begin();


	if(key==VK_RETURN)
	{
	}else if(key==SDLK_t)
	{

		// Stop rotation
		iter = bmap.begin();
		while(iter != bmap.end())
		{
			if(iter->second->getAngularVelocity() != 0)
			{
				iter->second->setAngle(0);
				iter->second->setAngularVelocity(0);

			}else
			{
				float av = (float)(rand() % 2) + 1.0f;
				iter->second->setAngularVelocity(av);
			}

			iter++;
		}

	}else if(key==SDLK_g)
	{
		if(forces)
			forces = false;
		else
			forces = true;
		
	}else if(key==SDLK_s)	
	{

		// Stop linear movement
		iter = bmap.begin();
		while(iter != bmap.end())
		{
			iter->second->setDisplacement(Vextor(0,0));
			iter++;
		}



	}else if(key==SDLK_p)
	{
		useSpatialPartitioning = useSpatialPartitioning ? false : true;

	}else if(key == SDLK_KP_PLUS)
	{
		float x = (float)(rand() % 3900) + 100.0f;
		float y = 200.0f;
		bodies.add(createBody4p(Vextor(x, y), Vextor(-25, -25), Vextor(-25, 25), Vextor(25, 25), Vextor(25, -25), 0.7f));

	}else if(key == SDLK_KP_MINUS)
	{
	}else if(key==SDLK_r)
	{
		ss->reset(3);
	}
}

void CollisionGame::keyReleased(int key)
{

}

void CollisionGame::mousePressed(float x, float y)
{

}

void CollisionGame::mouseReleased(float x, float y)
{

}

void CollisionGame::eventFired(Event e)
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
	}

}