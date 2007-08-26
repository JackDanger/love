/**
* @file LuaFile.h
* @author Anders Ruud
* @date 2006-12-18
* @brief Contains definition for class LuaFile.
**/

#ifndef LOVE_LUAFILE_H
#define LOVE_LUAFILE_H

// LOVE
#include "Object.h"
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class LuaFile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-12-18
	* @brief 
	**/
	class LuaFile : public Object, public Loadable
	{
	private:

		// file
		string file;

	public:

		/**
		* @brief Contructs an empty LuaFile.
		**/
		LuaFile();

		/**
		* @brief Constructs a Lua file from the filename.
		**/
		LuaFile(const string & file);

		virtual ~LuaFile();

		/**
		* @brief Gets file.
		* @return file.
		**/
		const string & getFile() const;


		/**
		* @brief Sets file.
		* @param file 
		**/
		void setFile(string file);

		void load();

		void unload();


	};

	typedef boost::shared_ptr<LuaFile> pLuaFile;

} // love

#endif

