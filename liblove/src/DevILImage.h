/**
* @file DevILImage.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class DevILImage.
**/

#ifndef LOVE_DEVILIMAGE_H 
#define LOVE_DEVILIMAGE_H 

// LOVE
#include "AbstractImage.h"
#include "Resource.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class AbstractFile;

	/**
	* @class DevILImage
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class DevILImage : public AbstractImage, public Resource
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty DevILImage.
		**/
		DevILImage(AbstractFile * file);
		
		/**
		* @brief Destructor.
		**/
		virtual ~DevILImage();

		/**
		* @brief Loads the image.
		* @return LOVE_OK if no errors.
		**/
		int load();

		/**
		* @brief Unloads the image.
		**/
		void unload();
		
	private:
		
		/**
		* @brief Converts a number to the nearest power of two. (ceil)
		* @param num The number to convert.
		* @return The converted number.
		**/
		int twoPower(int num) const;

		/**
		* @brief Pads the image to a power of two texture.
		* Useful for < OGL2.0, which only supports these.
		**/
		void padTwoPower();

		
	}; // DevILImage
	
	typedef boost::shared_ptr<DevILImage> pDevILImage;
	
} // love

#endif
