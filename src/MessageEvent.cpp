#include "MessageEvent.h"

namespace love
{

	MessageEvent::MessageEvent()
	{
		setType(LOVE_TYPE_MESSAGE_EVENT);
	}

	MessageEvent::MessageEvent(string message)
	{
		setType(LOVE_TYPE_MESSAGE_EVENT);
		this->message = message;
	}

	MessageEvent::~MessageEvent()
	{
	}

	const string & MessageEvent::getMessage() const
	{
		return message;
	}

	void MessageEvent::setMessage(string message)
	{
		this->message = message;
	}


}// love