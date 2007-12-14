#include "MessageEvent.h"

namespace love
{

	MessageEvent::MessageEvent()
	{
		setType(LOVE_TYPE_MESSAGE_EVENT);
	}

	MessageEvent::MessageEvent(std::string message)
	{
		setType(LOVE_TYPE_MESSAGE_EVENT);
		this->message = message;
	}

	MessageEvent::~MessageEvent()
	{
	}

	const char * MessageEvent::getMessage() const
	{
		return message.c_str();
	}


}// love
