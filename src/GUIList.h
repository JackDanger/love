#ifndef LOVE_GUI_LIST_H
#define LOVE_GUI_LIST_H

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>

using std::string;
using std::vector;

namespace love
{
	class GUIList : public gcn::ListModel
	{
	private:
		vector<string> list;
		vector<string>::iterator iter;

	public:
		int getNumberOfElements();
		string getElementAt(int i);

		void add(string text);
		void remove(int i);
		void clear();
	};

	typedef boost::shared_ptr<GUIList> pGUIList;
}

#endif