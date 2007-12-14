#ifndef LOVE_GUI_LIST_H
#define LOVE_GUI_LIST_H

#include <boost/shared_ptr.hpp>
#include <guichan.hpp>


namespace love
{
	class GUIList : public gcn::ListModel
	{
	private:
		std::vector<std::string> list;
		std::vector<std::string>::iterator iter;

	public:
		int getNumberOfElements();
		std::string getElementAt(int i);

		void add(std::string text);
		void remove(int i);
		void clear();
	};

	typedef boost::shared_ptr<GUIList> pGUIList;
}

#endif

