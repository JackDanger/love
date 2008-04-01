%module mod_physfs

%{
#include <boost/shared_ptr.hpp>
#include "love_physfs.h"
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%rename(shared_File) love::File;
%include ../File.i
%include File.i


namespace love_physfs
{
	pFile newFile(const char * file, int mode = READ);
	void require( const char * file );
	void include( const char * file );
	bool exists(const char * file);
	bool isDirectory(const char * file);
	bool isFile(const char * file);
	bool mkdir(const char * file);
	bool remove(const char * file);
	bool open(pFile & file);
	bool close(pFile & file);
	const char * read(pFile & file, int count = -1);
	bool write(pFile & file, const char * data);
	bool eof(pFile & file);
	int tell(pFile & file);
	bool seek(pFile & file, int pos);
}