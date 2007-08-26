#ifndef LOVE_ABSTRACT_STATE_H
#define LOVE_ABSTRACT_STATE_H

#include "Loadable.h"
#include "Renderable.h"
#include "Updateable.h"
#include "Object.h"
#include "Scriptable.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* @brief Like entity, but without position.
	* @see Entity
	**/
	class AbstractState// : public Object, public Renderable, public Updateable, public Scriptable, public Loadable
	{
	private:
	public:
	};

	typedef boost::shared_ptr<AbstractState> pAbstractState;
}

#endif
