#include "GUIList.h"

namespace love
{
	int GUIList::getNumberOfElements()
	{
		return (int)list.size();
	}

	string GUIList::getElementAt(int i)
	{
		if(i < 0 || i > (int)list.size())
			return "";
		return list[i];
	}

	void GUIList::add(string text)
	{
		list.push_back(text);
	}

	void GUIList::remove(int i)
	{
		iter = list.begin();
		for(int j = 0; j != i; j++)
			iter++;

		list.erase(iter);
	}

	void GUIList::clear()
	{
		list.clear();
	}
}
