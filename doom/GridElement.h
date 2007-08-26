#ifndef LOVE_GRID_ELEMENT
#define LOVE_GRID_ELEMENT

#include <vector>

// boost
#include <boost/shared_ptr.hpp>

using std::vector;

namespace love
{

	class Cell;
	class Vextor;

	class GridElement 
	{
	private:

		// Which Grid level the element starts on
		int level;

		Cell * parentCell;

	public:

		GridElement();
		virtual ~GridElement();

		int getLevel();
		void setLevel(int level);

		void setParentCell(Cell * c);

		Cell * getParentCell();

		void removeFromCell();

		virtual const Vextor & getInsertionPosition() = 0;

		virtual float getInsertionRadius() = 0;

		virtual int getGridElementId() = 0;

	};

	typedef boost::shared_ptr<GridElement> pGridElement;

}// love

#endif