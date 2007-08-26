#include "DisplayModeListener.h"

namespace love
{

	DisplayModeListener::DisplayModeListener() : num(0)
	{
	}

	DisplayModeListener::~DisplayModeListener()
	{
	}

	void DisplayModeListener::displayModeChanged()
	{
		num++;
	}

	bool DisplayModeListener::isDisplayModeChanged() const
	{
		return (num > 0);
	}
	
	int DisplayModeListener::getDisplayModeChangedNum() const
	{
		return num;
	}

	void DisplayModeListener::resetDisplayModeListener()
	{
		num = 0;
	}


}// love
