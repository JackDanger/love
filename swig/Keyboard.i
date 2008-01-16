%{#include "Keyboard.h"%}

namespace love
{

	class Keyboard : public Device
	{
	protected:	
	public:				
		virtual bool isDown(int key) const = 0;
	};
	
}