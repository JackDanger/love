#include "BoundingBox.h"

namespace love_chipmunk
{
	BoundingBox::BoundingBox()
	{
		b = cpBBNew(0, 0, 0, 0);
	}

	BoundingBox::BoundingBox(float l, float b, float r, float t)
	{
		this->b = cpBBNew(l, b, r, t);
	}

	BoundingBox::BoundingBox(cpBB b)
	{
		this->b = b;
	}

	bool BoundingBox::intersects(const boost::shared_ptr<BoundingBox> & b) const
	{
		return (cpBBintersects(this->b, b->b)!=0);
	}

	bool BoundingBox::contains(const boost::shared_ptr<BoundingBox> & b) const
	{
		return (cpBBcontainsBB(this->b, b->b)!=0);
	}

	bool BoundingBox::contains(const pVector & v) const
	{
		return (cpBBcontainsVect(b, v->v)!=0);
	}

	pVector BoundingBox::clamp(const pVector & v) const
	{
		pVector t(new Vector(cpBBClampVect(b, v->v)));
		return t;
	}

	pVector BoundingBox::wrap(const pVector & v) const
	{
		pVector t(new Vector(cpBBWrapVect(b, v->v)));
		return t;
	}

} // love_chipmunk