%{#include "File.h"%}

namespace love_physfs
{
	class File : public love::File
	{
	public:
		int getSize();
	};
	
	typedef boost::shared_ptr<File> pFile;
}

%template(SmartFile_physfs) boost::shared_ptr<love_physfs::File>;
