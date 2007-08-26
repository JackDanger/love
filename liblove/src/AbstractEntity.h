#ifndef LOVE_ABSTRACT_ENTITY_H
#define LOVE_ABSTRACT_ENTITY_H

#include "Renderable.h"
#include "Updateable.h"
#include "Object.h"
#include "Scriptable.h"
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* @brief Like entity, but without position.
	* @see Entity
	**/
	class AbstractEntity : public Object, public Renderable, public Updateable, public Scriptable
	{
	private:
	public:
		virtual void update(float dt);
		virtual void render();
	};

	typedef boost::shared_ptr<AbstractEntity> pAbstractEntity;
}

#endif
