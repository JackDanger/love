#include "BoostGame.h"
#include "Core.h"
#include "Point.h"
#include <typeinfo>

using love::Object;

using love::Entity;
using love::Container;
using love::pPoint;

#include <bitset>
using std::bitset;

BoostGame::BoostGame()
{

}

BoostGame::~BoostGame()
{

}

void BoostGame::init()
{

	boost::shared_ptr<love::Point> v1(new love::Point(5,3));
	s1 = v1;

	printf("Point: %f, %f\n", v1->getX(), v1->getY());
	printf("Ebtity: %f, %f\n", v1->getX(), v1->getY());

	if(s1 == v1)
		printf("OMG! TEH SAME!\n");


	v1->xMove(2.1f);

	printf("Point: %f, %f\n", v1->getX(), v1->getY());
	printf("Ebtity: %f, %f\n", v1->getX(), v1->getY());

	boost::shared_ptr<love::Point> v2(new love::Point(105,101));

	
	//cp["cock"].reset<love::Point>(new love::Point(55,66));
	cp.create("cock", new love::Point(55,66));
	cp["cock2"] = v2;
	cp["cock3"] = v2;

	love::pPoint pp(new love::Point(896,585));

	cp["cock4"] =  pp;

	love::pPoint pt = cp["cock4"];


	printf("Cock: %f, %f\n", cp["cock"]->getX(), cp["cock"]->getY());
	printf("Cock2: %f, %f\n", cp["cock2"]->getX(), cp["cock2"]->getY());

	if(cp["cock2"] == cp["cock3"])
		printf("OMG! TEH SAME AGAIN!\n");

	printf("\n\nOMGOMG\n\n");

	
	for( cp.begin() ; !cp.end() ; cp.next() )
	{
		printf("%s: %7.2f, %7.2f\n", cp.key().c_str(), cp.value()->getX(), cp.value()->getY());
	}

	cp.erase("cock");
	cp.erase("cock3");

	printf("\n\nOMGOMG ERASED:\n\n");

	for( cp.begin() ; !cp.end() ; cp.next() )
	{
		printf("%s: %7.2f, %7.2f\n", cp.key().c_str(), cp.value()->getX(), cp.value()->getY());
	}


	pPoint ppt(new Point(500,600));

	printf("ppt is: %s\n", typeid(ppt).name());

	printf("\nPoint: %f %f\n", ppt->getX(), ppt->getY());

	love::pObject po = boost::dynamic_pointer_cast<love::Object, love::Point>(ppt);

	printf("po is: %s\n", typeid(po).name());

	love::pPoint backp = boost::dynamic_pointer_cast<love::Point, love::Object>(po);

	printf("backp is: %s\n", typeid(backp).name());

	printf("\nbackp: %f %f\n", backp->getX(), backp->getY());


	setInited(true);
}

void BoostGame::render()
{

	
}

void BoostGame::update(float dt)
{


}

