#include "AbstractFile.h"

namespace love
{

	AbstractFile::AbstractFile(const string & source, const string & filename) : source(source), filename(filename)
	{
		this->data = 0;
		this->size = 0;
	}

	AbstractFile::~AbstractFile()
	{
		this->unload();
	}

	const string & AbstractFile::getSource() const
	{
		return source;
	}

	const string & AbstractFile::getFilename() const
	{
		return filename;
	}

	unsigned long AbstractFile::getSize() const
	{
		return size;
	}

	char * AbstractFile::getData()
	{
		return this->data;
	}

	void AbstractFile::unload()
	{
		if(data != 0)
			delete data;

		data = 0;
	}

}// love
