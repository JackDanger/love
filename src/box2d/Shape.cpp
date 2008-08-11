#include "Shape.h"

// Module
#include "Body.h"

namespace love_box2d
{
	Shape::Shape(boost::shared_ptr<Body> body)
		: body(body)
	{
		data = new shapeudata();
	}

	Shape::~Shape()
	{
		delete data;
		data = 0;
	}

	int Shape::setData(lua_State * L)
	{
		love::luax_assert_argc(L, 1, 1);
		data->ref.reset<love::Reference>(new love::Reference(L));
		return 0;
	}

	int Shape::getData(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		if(data->ref != 0)
			data->ref->push();
		else
			lua_pushnil(L);

		return 1;
	}

} // love_box2d