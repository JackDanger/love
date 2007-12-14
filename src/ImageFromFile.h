/**
* @file ImageFromFile.h
* @author Anders Ruud
* @date 2007-01-27
* @brief Contains definition for class ImageFromFile.
**/

#ifndef LOVE_IMAGE_FROM_FILE_H
#define LOVE_IMAGE_FROM_FILE_H

// LOVE
#include "AbstractImage.h"
#include "Resource.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

// DevIL
#include <IL/ilut.h>
#include <string>

namespace love
{

	/**
	* @class ImageFromFile
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-01-27
	* @brief 
	**/
	class ImageFromFile : public AbstractImage, public Resource
	{
	private:


		int twoPower(int num) const;
		void padTwoPower();

	public:


		ImageFromFile(AbstractFile * file);

		virtual ~ImageFromFile();

		/**
		* @brief Gets filename.
		* @return filename.
		**/
		const std::string & getFilename() const;

		int load();

		void unload();




	};

	typedef boost::shared_ptr<ImageFromFile> pImageFromFile;

} // love

#endif

