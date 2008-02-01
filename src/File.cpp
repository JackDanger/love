#include "File.h"

using std::string;

namespace love
{
	File::File(const string & source, const string & filename, char *data, const unsigned long size, bool compiled)
		: source(source), filename(filename), data(data), size(size), compiled(compiled)
	{
	}

	File::File(const string & source, const string & filename) 
		: source(source), filename(filename), data(0), size(0), compiled(false)
	{
	}

	File::~File()
	{
		this->unload();
	}

	const string & File::getSource() const
	{
		return source;
	}

	const string & File::getFilename() const
	{
		return filename;
	}

	unsigned long File::getSize() const
	{
		return size;
	}

	char * File::getData()
	{
		return this->data;
	}

	void File::unload()
	{
		if(data != 0 && !compiled)
			delete data;

		data = 0;
	}

}// love
