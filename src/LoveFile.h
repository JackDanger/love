/**
* @file LoveFile.h
* @author Anders Ruud
* @date 2007-08-05
* @brief Contains definition for class LoveFile.
**/

#ifndef LOVE_LOVEFILE_H
#define LOVE_LOVEFILE_H

// LOVE
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class LoveFile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-05
	* @brief 
	**/
	class LoveFile : public Loadable
	{
	private:

		// source
		string source;

		// filename
		string filename;

		// The actual file data
		char * data;

		// The size of the data
		unsigned long size;

	public:

		/**
		* @brief Contructs an empty LoveFile.
		**/
		LoveFile();

		LoveFile(const string & source, const string & filename);

		virtual ~LoveFile();

		/**
		* @brief Gets source.
		* @return source.
		**/
		const string & getSource() const;


		/**
		* @brief Gets filename.
		* @return filename.
		**/
		const string & getFilename() const;


		unsigned long getSize() const;

		char * getData();


		void load();
		void unload();

		

	private:

		void fail();
		void removeSource();


	};

	typedef boost::shared_ptr<LoveFile> pLoveFile;

} // love

#endif

