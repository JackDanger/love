#ifndef LOVE_CONFIGURATION_H
#define LOVE_CONFIGURATION_H

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
	* @class Configuration
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-03-03
	* @brief Handles the config files that accompanies every game.
	**/
	class Configuration : public Resource, public Loadable
	{
	private:
		map<string, string> data; // the configuration data
		string filepath; // path to a file to load
		char buffer [33]; // buffer for changing from number to string

	public:
		/**
		 * @param filepath The path to the config file.
		 * @brief Sets the local private filepath variable.
		 **/
		Configuration();
		Configuration(string filepath);
		Configuration(pAbstractFile file);
		~Configuration();

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
		 * @param key The key of the value to be checked.
		 * @return Whether the key exists.
		 * @brief Checks the list of values to see whether the key exists.
		 **/
		bool exists(string key);

		/**
		 * @param key The key of the new string.
		 * @param value The string itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addString(string key, string value);
		void add(string key, string value);

		/**
		 * @param key The key of the new boolean.
		 * @param value The boolean itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addBool(string key, bool value);
		void add(string key, bool value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addFloat(string key, float value);
		void add(string key, float value);

		/**
		 * @param key The key of the new number.
		 * @param value The number itself.
		 * @brief If the key does not already exist in the list, it is replaced by the new value
		 **/
		void addInt(string key, int value);
		void add(string key, int value);

		/**
		 * @brief Writes the config keys and values to a file.
		 **/
		void write();
	};

	typedef boost::shared_ptr<Configuration> pConfiguration;
}

#endif
