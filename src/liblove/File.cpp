#include <love/File.h>

using std::string;

namespace love
{
	File::File(const string & filename, char *data, const unsigned long size, bool compiled)
		: filename(filename), data(data), size(size), compiled(compiled), mode(FILE_READ), isOpen(false)
	{
	}

	File::File(const string & filename, int mode) 
		: filename(filename), data(0), size(0), compiled(false), mode(mode), isOpen(false)
	{
	}

	File::~File()
	{
		if(data != 0 && !compiled)
			delete data;

		data = 0;
	}

	const string & File::getFilename() const
	{
		return filename;
	}

	void File::allocate(int size)
	{
		if(data != 0)
			return;
		data = new char[size];
	}

	unsigned long File::getSize() const
	{
		return size;
	}

	void File::setSize(int size)
	{
		this->size = size;
	}

	int File::getMode() const
	{
		return mode;
	}

	char * File::getData()
	{
		return this->data;
	}

	void File::setData( char * data )
	{
		this->data = data;
	}

	bool File::isCompiled() const
	{
		return compiled;
	}

}// love
