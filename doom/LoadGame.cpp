#include "LoadGame.h"
#include "Core.h"

LoadGame::LoadGame()
{

}

LoadGame::~LoadGame()
{

}

pLoadTest getLoadTest(int a, string b)
{
	pLoadTest lt(new LoadTest(a, b));
	return lt;
}

void LoadGame::init()
{

	font = new Font("Arial", 26);


	loader.reset<Loader>(new Loader(this));
	loader->setParentLoadListener(this);

	loader->add(getLoadTest(2, "Cocks"));
	loader->add(getLoadTest(50000, "OMG, Getting harder"));
	loader->add(getLoadTest(50000000, "ZOMG! HARD PT 1"));
	loader->add(getLoadTest(99999999, "ZOMG! HARD PT 2"));
	loader->add(getLoadTest(99999999, "ZOMG! HARD PT 3"));
	loader->add(getLoadTest(99999999, "ZOMG! HARD PT 4"));
	loader->add(getLoadTest(99999999, "ZOMG! HARD PT 5"));
	loader->add(getLoadTest(99999999, "OMG LOLI"));
	loader->add(getLoadTest(99999999, "MAMMOTH FIB PLZ! -.- (TAKES LONG TIME, PLEASE WAIT LOL)"));
	loader->add(getLoadTest(50000000, "ZOMG! HARD PT 1"));
	loader->add(getLoadTest(50000000, "ZOMG! HARD PT 1"));
	loader->add(getLoadTest(50000000, "ZOMasdfT 1"));
	loader->add(getLoadTest(50000000, "ZOMasdf1"));
	loader->add(getLoadTest(50000000, "ZOMGasdf 1"));
	loader->add(getLoadTest(50000000, "ZOMG! HAasdf"));
	loader->add(getLoadTest(50000000, "ZOMG!asdf"));
	loader->add(getLoadTest(50000000, "ZOMG!asdf"));
	loader->add(getLoadTest(90000000, "WHAT THE FUCK IT NEVER ENDS!"));
	loader->add(getLoadTest(50000000, "ZOMGasdf"));
	loader->add(getLoadTest(50000000, "asdf"));
	loader->add(getLoadTest(50000000, "ZOMG! HARD Pasfasdfasdf"));
	loader->add(getLoadTest(50000000, "ZOMG! HAasdfasdf"));




	loader->add(getLoadTest(1, "Done!"));

	loader->load();

	setInited(true);
}

void LoadGame::render()
{

	glColor3ub(255,255,255);
	glTranslatef(50,50,0);
	font->print(loader->getLoadDescription().c_str());
	glTranslatef(0,50,0);
	font->print("Progress: %7.2f\n", (loader->getProgress()*100));

}

void LoadGame::update(float dt)
{


}
void LoadGame::loadStateChanged()
{
	Core::render();
}