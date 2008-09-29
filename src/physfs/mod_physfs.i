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

%include File.i


namespace love_physfs
{
	bool setIdentity(const char * ident);
	bool setSource(const char * source);
	pFile newFile(const char * file, int mode = READ);
	const char * getWorkingDirectory();
	const char * getUserDirectory();
	const char * getAppdataDirectory();
	const char * getSaveDirectory();
	bool exists(const char * file);
	bool isDirectory(const char * file);
	bool isFile(const char * file);
	bool mkdir(const char * file);
	bool remove(const char * file);
	bool open(pFile & file);
	bool close(pFile & file);
	bool eof(pFile & file);
	int tell(pFile & file);
	bool seek(pFile & file, int pos);
}

%native(enumerate) int love_physfs::enumerate(lua_State * L);
%native(lines) int love_physfs::lines(lua_State * L);
%native(read) int love_physfs::read(lua_State * L);
%native(write) int love_physfs::write(lua_State * L);
%native(load) int love_physfs::load(lua_State * L);

%luacode {
love.filesystem = mod_physfs

-- Contains included files.
love.filesystem.is_included = {}

function love.filesystem.include(filename)
	local f = love.filesystem.load(filename)
	return f()
end

function love.filesystem.require(filename)
	if not love.filesystem.is_included[filename] then
		love.filesystem.include(filename)
		love.filesystem.is_included[filename] = true
	end
end

}