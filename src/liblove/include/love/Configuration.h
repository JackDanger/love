/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CONFIGURATION_H
#define LOVE_CONFIGURATION_H

// LOVE
#include "Resource.h"

// STD
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>


namespace love
{
	/**
	* Handles the config files that accompanies every game.
	*
	* @author Michael Enger
	* @date 2007-03-03
	**/
	class Configuration : public Resource
	{
	private:
		std::map<std::string, std::string> data; // the configuration data
		std::string filepath; // path to a file to load

	public:

		/**
		 * @param filepath The path to the config file.
		 * @brief Sets the local private filepath variable.
		 **/
		Configuration(pFile file);
		~Configuration();

		virtual bool load();
		virtual void unload();

		/**
		 * @param key The key of the sought value.
		 * @return The sought string value.
		 * @brief Returns the string value associated with the key, or returns an empty string if the key does not exist.
		 **/
		std::string getString(std::string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought boolean value.
		 * @brief Returns the boolean value associated with the key , or returns false if the key does not exist.
		 **/
		bool getBool(std::string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought float value.
		 * @brief Returns the float value associated with the key, or returns 0 if the key does not exist.
		 **/
		float getFloat(std::string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought integer value.
		 * @brief Returns the integer value associated with the key, or returns 0 if the key does not exist.
		 **/
		int getInt(std::string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a string.
		 * @brief Checks the list of strings to see whether the key exists.
		 **/
		bool isString(std::string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a boolean.
		 * @brief Checks the list of booleans to see whether the key exists.
		 **/
		bool isBool(std::string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a number.
		 * @brief Checks the list of numbers to see whether the key exists.
		 **/
		bool isFloat(std::string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a number.
		 * @brief Checks the list of numbers to see whether the key exists.
		 **/
		bool isInt(std::string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists.
		 * @brief Checks the list of values to see whether the key exists.
		 **/
		bool exists(std::string key);

		/**
		 * @param key The key of the new string.
		 * @param value The string itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void add(std::string key, std::string value);

		/**
		 * @param key The key of the new boolean.
		 * @param value The boolean itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void add(std::string key, bool value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void add(std::string key, float value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void add(std::string key, int value);

		/**
		 * @brief Writes the config keys and values to a file.
		 **/
		void write();

	}; // Configuration

} // love

#endif // LOVE_CONFIGURATION_H
