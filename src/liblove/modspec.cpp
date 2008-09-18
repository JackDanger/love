#include <love/modspec.h>

// STD
#include <iostream>

/**
* Quick macro to make verification simpler.
* p - The function pointer.
* f - The name of the function.
* m - The name of the module.
**/
#define VERIFY(p, f, m) \
	if(p==0) \
	{ \
		std::cerr << "Error: missing function pointer " \
				  << m << ":" << f << "()." << std::endl; \
		return false; \
	} \

#define CHECK_LOAD(m) \
	if(!loaded) \
	{ \
		std::cerr << "Error: module " << m << " not loaded." \
		<< std::endl; \
		return false; \
	} \


namespace love
{
	modspec::modspec()
		: loaded(false)
	{
	}

	Filesystem::Filesystem()
	{
		getFile = 0;
		exists = 0;
		setSaveDirectory = 0;
		addDirectory = 0;
		getBaseDirectory = 0;
	}

	bool Filesystem::verify()
	{
		CHECK_LOAD("Filesystem");
		VERIFY(getFile, "getFile", "Filesystem");
		VERIFY(exists, "exists", "Filesystem");
		VERIFY(setSaveDirectory, "setSaveDirectory", "Filesystem");
		VERIFY(addDirectory, "addDirectory", "Filesystem");
		VERIFY(getBaseDirectory, "getBaseDirectory", "Filesystem");
		return loaded;
	}

	Graphics::Graphics()
	{
		clear = 0;
		present = 0;
		reset = 0;
		setMode = 0;
		isCreated = 0;
		setCaption = 0;
	}

	bool Graphics::verify()
	{
		CHECK_LOAD("Graphics");
		VERIFY(clear, "clear", "Graphics");
		VERIFY(present, "present", "Graphics");
		VERIFY(reset, "reset", "Graphics");
		VERIFY(setMode, "setMode", "Graphics");
		VERIFY(isCreated, "isCreated", "Graphics");
		VERIFY(setCaption, "setCaption", "Graphics");
		return loaded;
	}

	Timer::Timer()
	{
		step = 0;
		getDelta = 0;
	}

	bool Timer::verify()
	{
		CHECK_LOAD("Timer");
		VERIFY(step, "step", "Timer");
		VERIFY(getDelta, "getDelta", "Timer");
		return true;
	}

	System::System()
	{
		getGame = 0;
		error = 0;
	}

	bool System::verify()
	{
		CHECK_LOAD("System");
		VERIFY(getGame, "getGame", "System");
		VERIFY(error, "error", "System");
		return loaded;
	}

	/**
	* These modules currently have no required
	* function pointers.
	**/

	bool Audio::verify()
	{
		CHECK_LOAD("Audio");
		return true;
	}

	bool Mouse::verify()
	{
		CHECK_LOAD("Mouse");
		return true;
	}

	bool Keyboard::verify()
	{
		CHECK_LOAD("Keyboard");
		return true;
	}

	bool Joystick::verify()
	{
		CHECK_LOAD("Joystick");
		return true;
	}

} // love
