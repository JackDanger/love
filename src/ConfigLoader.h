#ifndef LOVE_CONFIGLOADER_H
#define LOVE_CONFIGLOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>

#include "Resource.h"
#include "Loadable.h"

using std::string;
using std::vector;
using std::map;
using namespace std;

namespace love
{
	/**
	* @class ConfigLoader
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-03-03
	* @brief Handles the config files that accompanies every game.
	**/
	class ConfigLoader : public Resource, public Loadable
	{
	private:
		map<string, string> text;
		map<string, bool> boolean;
		map<string, double> number;
		
		string filepath;

	public:
		/**
		 * @param filepath The path to the config file.
		 * @brief Sets the local private filepath variable.
		 **/
		ConfigLoader();
		ConfigLoader(string filepath);
		ConfigLoader(AbstractFile * file);

		virtual int load();
		virtual void unload();

		/**
		 * @param key The key of the sought value.
		 * @return The sought string value.
		 * @brief Returns the string value associated with the key, or returns an empty string if the key does not exist.
		 **/
		string getString(string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought boolean value.
		 * @brief Returns the boolean value associated with the key , or returns false if the key does not exist.
		 **/
		bool getBool(string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought float value.
		 * @brief Returns the float value associated with the key, or returns 0 if the key does not exist.
		 **/
		float getFloat(string key);

		/**
		 * @param key The key of the sought value.
		 * @return The sought integer value.
		 * @brief Returns the integer value associated with the key, or returns 0 if the key does not exist.
		 **/
		int getInt(string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a string.
		 * @brief Checks the list of strings to see whether the key exists.
		 **/
		bool isString(string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a boolean.
		 * @brief Checks the list of booleans to see whether the key exists.
		 **/
		bool isBool(string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a number.
		 * @brief Checks the list of numbers to see whether the key exists.
		 **/
		bool isFloat(string key);

		/**
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists as a number.
		 * @brief Checks the list of numbers to see whether the key exists.
		 **/
		bool isInt(string key);

		/**
		 * @param key The key of the new string.
		 * @param value The string itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addString(string key, string value);

		/**
		 * @param key The key of the new boolean.
		 * @param value The boolean itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addBool(string key, bool value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addFloat(string key, float value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addInt(string key, float value);

		/**
		 * @brief Writes the config keys and values to a file.
		 **/
		void write();
	};

	typedef boost::shared_ptr<ConfigLoader> pConfigLoader;
}

#endif
