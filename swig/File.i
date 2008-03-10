%{#include "File.h"%}

namespace love
{
	class File
	{
	private:
	public:
		unsigned long getSize() const;
	};
	
	typedef boost::shared_ptr<File> pFile;
}

%template(SmartFile) boost::shared_ptr<love::File>;