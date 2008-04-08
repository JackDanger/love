#include "love_physfs.h"

// STD
#include <set>
#include <string>

// PhysFS
#include <physfs.h>

// For great CWD. (Current Working Directory)
// Using this instead of boost::filesystem which totally
// cramped our style.
#ifdef WIN32
#	include <direct.h>
#else
#	include <sys/param.h>
#	include <unistd.h>
#endif

// From SWIG.
extern "C" {
	int luaopen_mod_physfs(lua_State * L);
}

namespace love_physfs
{

	// List of filesystem states.
	std::vector<state> states;

	// Counts open files.
	int open_count = 0;

	// Pointer used for file reads.
	char * buffer = 0;

	// Set of included files.
	std::set<std::string> included;

	bool init(love_mod::modconf * conf)
	{
		if(!PHYSFS_init(conf->argv[0]))
			return error("Could not init PhysFS");
		love_mod::setConf(conf);
		love_mod::report_init("love.filesystem", "PhysFS");
		return true;
	}

	bool quit()
	{
		if(!PHYSFS_deinit())
			return false;
		love_mod::report_init("love.filesystem", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		included.clear();
		love_mod::setL(s);
		luaopen_mod_physfs(s);
		love_mod::do_string("love.filesystem = mod_physfs");
		return true;
	}

	bool load(love::pFile & file)
	{
		if( file->isCompiled() ) 
			return true; // We're already loaded.
	
		// Get the filename.
		std::string filename = file->getFilename();

		// Clear what's in it.
		file.reset();

		// Check for file existence.
		if(!exists(filename.c_str()))
		{
			love_mod::runtime_error("File " + filename + " does not exist.");
			return false;
		}

		// Create the new file.
		pFile f = newFile(filename.c_str());

		// Try to open it.
		if(!open(f))
			return false;
		
		// Okay, get the filesize and allocate that much memory.
		f->setSize((int)PHYSFS_fileLength(f->getHandle()));
		f->allocate(f->getSize());
		
		// Read the file.
		if(PHYSFS_read(f->getHandle(), f->getData(), 1, f->getSize()) == -1)
		{
			love_mod::runtime_error("Data could not be read from " + filename + ".");
			close(f);
			return false;
		}

		close(f);
		file = f;
		return true;
	
	}

	bool unload(love::pFile & file)
	{
		if(file == 0)
			return true;

		if(file->isCompiled())
			return true; // Never unload compiled files ...

		char * data = file->getData();

		if(data != 0)
		{
			delete [] data;
			file->setData(0);
		}

		return true;
	}


	bool push()
	{
		// We can only push if no files are open.
		if(open_count != 0)
			return false;

		// Remove the current state from PhysFS, if any.
		if(!states.empty())
			removeState(states.back());

		// Okay, push a fresh state.
		state s;
		states.push_back(s);
		return true;
	}

	bool pop()
	{
		// We can only pop if no files are open.
		if(open_count != 0)
			return false;

		// Do not pop an empty state stack.
		if(states.empty())
			return false;

		// Remove the old state from PhysFS.
		removeState(states.back());

		// Remove the old state from stack.
		states.pop_back();

		// Restore previous state.
		if(!states.empty())
			addState(states.back());
			
		return true;
	}

	bool error(const std::string & s)
	{
		std::string e(PHYSFS_getLastError());
		love_mod::runtime_error( s + e );
		return false;
	}
	
	bool addState( state & s )
	{
		// Add search directories.
		std::vector<std::string>::iterator i = s.search.begin();
		while( i != s.search.end() )
		{
			if(!addDir((*i)))
				return false;
			i++;
		}

		// Set write directory.
		if(!setWriteDir(s.write))
			return false;
		return true;
	}

	bool removeState( state & s )
	{
		// Remove search directories.
		std::vector<std::string>::iterator i = s.search.begin();
		while( i != s.search.end() )
		{
			if(!removeDir((*i)))
				return false;
			i++;
		}

		// Remove write directory.
		if(!disableWriteDir())
			return false;
		return true;
	}

	void getUserDir(std::string & user)
	{
		const char * dir = PHYSFS_getUserDir();

		if(dir == 0) 
			return;
		
		user = std::string(dir);
	}

	void getBaseDir(std::string & base)
	{

#ifdef WIN32
		char * buf = _getcwd(0, 0);
#else
		char buf[MAXPATHLEN];
		getcwd(buf, MAXPATHLEN);
#endif

		if(buf == 0)
		{
			base = "";
			return;
		}
		else
		{
			base = std::string(buf) + "/";
		}

	}

	bool setSaveDirectory( const std::string & gameid )
	{

		// Get user directory.
		std::string user;
		getUserDir(user);

		// Create the .love directory.
		if(!setWriteDir(user))
			return false;

		// Create the love folder.
		if(!mkdir(".love"))
		{
			printf(PHYSFS_getLastError());
			disableWriteDir();
			return false;
		}

		// Set the love folder as the write directory.
		if(!setWriteDir(user + ".love"))
			return false;

		// Create the game folder.
		if(!mkdir(gameid.c_str()))
		{
			printf(PHYSFS_getLastError());
			disableWriteDir();
			return false;
		}

		// Set this as the new directory.
		if(!setWriteDir(user + ".love/" + gameid))
			return false;

		// Also add this dir to the search path.
		if(!addDir(user + ".love/" + gameid))
			return false;

		return true;
	}

	void getLeaf( const std::string & full, std::string & leaf)
	{

		std::string l = full;

#ifdef WIN32
		
		// Replace all \ with /
		{
			size_t pos = l.find("\\");
			while(pos != std::string::npos)
			{
				l.replace(pos, 1, "/");
				pos = l.find("\\", pos+1);
			}
		}
#endif

		// Get the name after the last slash.
		size_t pos = l.find_last_of("/");

		if(pos == std::string::npos)
		{
			// The path is already the leaf.
			leaf = l;
			return;
		}

		// Extract leaf.
		leaf = l.substr(pos+1);
	}

	std::string getWriteDir()
	{
		const char * dir = PHYSFS_getUserDir();
		if(dir == 0)
			return std::string();
		return std::string(dir);
	}

	bool setWriteDir(const std::string & dir)
	{
		if(!PHYSFS_setWriteDir(dir.c_str()))
			return false;
		return true;
	}

	bool disableWriteDir()
	{
		if(!PHYSFS_setWriteDir(0))
			return false;
		return true;
	}

	bool addDir(const std::string & dir)
	{
		if(!PHYSFS_addToSearchPath(dir.c_str(), 1))
			return false;
		states.back().search.push_back(dir);
		return true;
	}

	bool exists(const std::string & f)
	{
		return exists(f.c_str());
	}

	bool addBase()
	{
		std::string base;
		getBaseDir(base);
		return addDir(base);
	}

	bool removeDir(const std::string & dir)
	{
		if(!PHYSFS_removeFromSearchPath(dir.c_str()))
			return false;
		return true;
	}

	pFile newFile(const char * file, int mode)
	{
		if(mode == love::FILE_READ && !exists(file))
		{
			std::string filename(file);
			love_mod::runtime_error("File " +filename+ " does not exist.\n");
		}

		pFile f(new File(std::string(file), mode));
		return f;
	}

	void require( const char * file )
	{
		std::string s(file);
		
		if(included.find(s) != included.end())
			return;

		// Okay, include it.
		included.insert(s);

		include(file);

	}


	void include( const char * file )
	{
		std::string s(file);
		
		if(!exists(file))
		{
			love_mod::runtime_error("Could not include " + s + ". File does not exist.");
			return;
		}

		love::pFile f(new File(std::string(file)));

		if(!load(f))
			return;

		int result = luaL_loadbuffer (	love_mod::getL(),
										(const char *)f->getData(), 
										f->getSize(),
										f->getFilename().c_str());

		// Could not load file, for some reason.
		if(result != 0)
		{
			// Get error message.
			const char * msg = lua_tostring(love_mod::getL(), -1);
			lua_pop(love_mod::getL(), 1);
			std::cout << msg << std::endl;
			//lualove_gui_error(msg);

			return;
		}

		// Run the loaded chunk.
		int status = love_mod::call(0);
		love_mod::handle_error(status);
	}

	bool exists(const char * file)
	{
		if(PHYSFS_exists(file))
			return true;
		return false;
	}

	bool isDirectory(const char * file)
	{
		if(PHYSFS_isDirectory(file))
			return true;
		return false;
	}

	bool isFile(const char * file)
	{
		return !isDirectory(file);
	}

	bool mkdir(const char * file)
	{
		if(!PHYSFS_mkdir(file))
			return false;
		return true;
	}

	bool remove(const char * file)
	{
		if(!PHYSFS_delete(file))
			return false;
		return true;
	}

	bool open(pFile & file)
	{

		// The to-be opened PhysFS file handle.
		PHYSFS_file * f = 0;

		switch(file->getMode())
		{
		case love::FILE_READ:
			f = PHYSFS_openRead(file->getFilename().c_str());
			break;
		case love::FILE_APPEND:
			f = PHYSFS_openAppend(file->getFilename().c_str());
			break;
		case love::FILE_WRITE:
			f = PHYSFS_openWrite(file->getFilename().c_str());
			break;
		}

		if(f == 0)
			return false;
		
		file->setHandle(f);
		open_count++;
		return true;
	}

	bool close(pFile & file)
	{
		if(file->getHandle() == 0)
			return false;

		if(!PHYSFS_close(file->getHandle()))
			return false;

		file->setHandle(0);
		open_count--;
		return true;
	}

	const char * read(pFile & file, int count)
	{
		if(file->getHandle() == 0)
			return false;

		if(count == -1)
			count = file->getSize();

		if(buffer != 0)
		{
			delete [] buffer;
			buffer = 0;
		}

		buffer = new char[count];

		if(PHYSFS_read(file->getHandle(), buffer, 1, count) == -1)
			return 0;

		return (const char *)buffer;
	}

	bool write(pFile & file, const char * data)
	{

		std::string str(data);

		unsigned int written = static_cast<unsigned int>(PHYSFS_write(file->getHandle(), data, 1, (PHYSFS_uint32)str.length()));

		if(written != str.length())
			return false;

		return true;
	}

	bool eof(pFile & file)
	{
		if(file->getHandle() == 0)
			return false;

		if(PHYSFS_eof(file->getHandle()))
			return true;
		return false;
	}

	int tell(pFile & file)
	{
		if(file->getHandle() == 0)
			return -1;

		return (int)PHYSFS_tell(file->getHandle());
	}

	bool seek(pFile & file, int pos)
	{
		if(file->getHandle() == 0)
			return false;
		
		if(!PHYSFS_seek(file->getHandle(), (PHYSFS_uint64)pos))
			return false;
		return true;
	}

} // love_physfs
