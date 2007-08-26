#ifndef LOVE_LOAD_TEST
#define LOVE_LOAD_TEST

#include "Loadable.h"
#include "Object.h"


// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class LoadTest : public Object, public Loadable
	{
	private:
	
		int p;
		int pp;
		int c;
		int m;

	public:

		LoadTest();
		LoadTest(int num, string desc);
		~LoadTest();

		void load();
		void unload();
	};

	typedef boost::shared_ptr<LoadTest> pLoadTest;

}
#endif
