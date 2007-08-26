#include "LoadTest.h"

namespace love
{

	LoadTest::LoadTest()
	{
		p = 1;
		pp = 1;
		m = 100;

		setLoadDescription("default");
	}
	LoadTest::LoadTest(int num, string desc)
	{

		p = 1;
		pp = 1;
		m = num;

		setLoadDescription(desc);
	}

	LoadTest::~LoadTest()
	{
	}

	void LoadTest::load()
	{
		for(int i=0;i<m;i++)
		{
			int c = p + pp;
			p = pp;
			pp = c;
		}

		string tmp = getLoadDescription() + " : Fib %i @ %i\n";

		printf(tmp.c_str(), m, pp); 
	}

	void LoadTest::unload()
	{
	}
}