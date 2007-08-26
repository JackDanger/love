#include "LuaFile.h"

namespace love
{

	LuaFile::LuaFile()
	{
	}

	LuaFile::LuaFile(const string & file)
	{
		this->file = file;
	}

	LuaFile::~LuaFile()
	{
	}

	const string & LuaFile::getFile() const
	{
		return file;
	}

	void LuaFile::setFile(string file)
	{
		this->file = file;
	}

	void LuaFile::load()
	{
		// @todo Do stuff here.
	}

	void LuaFile::unload()
	{
	}


}// love
