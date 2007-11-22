#include "ConfigLoader.h"
#include "Core.h"
#include "love.h"
#include "AbstractFile.h"

//not a part of the actual class, just here to help
string trim(string s, string drop = " ")
{
	string r = s.erase(s.find_last_not_of(drop) + 1);
	return r.erase(0, r.find_first_not_of(drop));
}

namespace love
{


	ConfigLoader::ConfigLoader(string filepath) : Resource(0), filepath(filepath)
	{

	}

	ConfigLoader::ConfigLoader(AbstractFile * file) : Resource(file), filepath("")
	{
	}

	int ConfigLoader::load()
	{
		string temp, key, value;
		int index ,line;

		istream * ifs;

		if(filepath != "")
		{
			ifs = new ifstream (filepath.c_str());
		}else
		{
			file->load();

			string s(file->getData(), file->getSize());

			ifs = new istringstream(s);
		}

		
		if(!ifs)
		{
			core->error("ConfigLoader: ERROR! Could not read file '%s'.\n", filepath.c_str());
			//printf("Config Loader: ERROR! Could not read file '%s'.\n", filepath.c_str());
			return LOVE_ERROR;
		}

		line = 0;
		while(getline(*ifs, temp))
		{
			line++;
			index = (int)temp.find_first_of('=', 0);
			if(index == (int)string::npos)
				core->printf("ConfigLoader (Line %d): Unrecognized command: \"%s\"\n", line, temp.c_str());
				//printf("Config Loader (Line %d): Unrecognized command: \"%s\"\n", line, temp.c_str());
			if(index != (int)string::npos && temp.find_first_of('#', 0) != 0 && trim(temp).size() != 0)
			{
				key = trim(temp.substr(0, index));
				value = trim(temp.substr(index + 1));

				string src = "\r";
				string dest = "";

				// Remove ALL \r
				for(string::size_type i = value.find(src, 0); i != string::npos; i = value.find(src, i))
				{
					value.replace(i, src.size(), dest);
				}

				//find the type of value
				if(value.compare("true") == 0 || value.compare("false") == 0)
				{
					if(boolean.count(key) != 0)
						core->printf("ConfigLoader (Line %d): The key '%s' already exists.\n", line, key.c_str());
						//printf("Config Loader (Line %d): The key '%s' already exists.\n", line, key.c_str());
					else
					{
						if(value.compare("true") == 0)
							boolean[key] = true;
						else
							boolean[key] = false;
					}
				}
				else if((int)value.find_first_of('"', 0) == 0 && value.find_last_of('"', value.size() - 1) == value.size() - 1)
				{
					if(text.count(key) != 0)
						core->printf("ConfigLoader (Line %d): The key '%s' already exists.\n", line, key.c_str());
						//printf("Config Loader (Line %d): The key '%s' already exists.\n", line, key.c_str());
					else
						text[key] = value.substr(1, value.size() - 2);
				}
				else //assumes number
				{
					//printf("Configloader: value =%s\n", value.c_str());
					if(number.count(key) != 0)
						core->printf("ConfigLoader (Line %d): The key '%s' already exists.\n", line, key.c_str());
						//printf("Config Loader (Line %d): The key '%s' already exists.\n", line, key.c_str());
					else
						number[key] = atof(value.c_str());
				}
			}
		}

		return LOVE_OK;
	}

	void ConfigLoader::unload()
	{
		text.clear();
		number.clear();
		boolean.clear();
	}

	string ConfigLoader::getString(string key)
	{
		if(text.count(key) != 0)
			return text[key];
		else
			return "";
	}

	bool ConfigLoader::getBool(string key)
	{
		if(boolean.count(key) != 0)
			return boolean[key];
		else
			return false;
	}

	float ConfigLoader::getFloat(string key)
	{
		if(number.count(key) != 0)
			return (float)number[key];
		else
			return 0;
	}
	
	int ConfigLoader::getInt(string key)
	{
		if(number.count(key) != 0)
			return (int)number[key];
		else
			return 0;
	}

	bool ConfigLoader::isString(string key)
	{
		if(text.count(key) != 0)
			return true;
		else
			return false;
	}

	bool ConfigLoader::isBool(string key)
	{
		if(boolean.count(key) != 0)
			return true;
		else
			return false;
	}

	bool ConfigLoader::isFloat(string key)
	{
		if(number.count(key) != 0)
			return true;
		else
			return false;
	}

	bool ConfigLoader::isInt(string key)
	{
		if(number.count(key) != 0)
			return true;
		else
			return false;
	}

	void ConfigLoader::addString(string key, string value)
	{
		//if(!isString(key))
			text[key] = value;
		//else
			//printf("Config Loader: The key '%s' already exists.\n", key.c_str());
	}

	void ConfigLoader::addBool(string key, bool value)
	{
		//if(!isBool(key))
			boolean[key] = value;
		//else
			//printf("Config Loader: The key '%s' already exists.\n", key.c_str());
	}

	void ConfigLoader::addFloat(string key, float value)
	{
		//if(!isFloat(key))
			number[key] = value;
		//else
			//printf("Config Loader: The key '%s' already exists.\n", key.c_str());
	}

	void ConfigLoader::addInt(string key, float value)
	{
		//if(!isInt(key))
			number[key] = value;
		//else
			//printf("Config Loader: The key '%s' already exists.\n", key.c_str());
	}

	void ConfigLoader::write()
	{
		ofstream file(filepath.c_str(), ios::trunc);
		if(!file)
		{
			core->error("ConfigLoader: ERROR! Could not write to file '%s'.\n", filepath.c_str());
			//printf("Config Loader: ERROR! Could not write to file '%s'.\n", filepath.c_str());
			return;
		}

		map<string, string>::iterator sIter;
		for(sIter = text.begin(); sIter != text.end(); sIter++)
		{
			file << sIter->first << " = \"" << sIter->second << "\"\n";
		}

		map<string, bool>::iterator bIter;
		for(bIter = boolean.begin(); bIter != boolean.end(); bIter++)
		{
			file << bIter->first << " = ";
			if(bIter->second)
				file << "true";
			else
				file << "false";
			file << "\n";
		}

		map<string, double>::iterator nIter;
		for(nIter = number.begin(); nIter != number.end(); nIter++)
		{
			file << nIter->first << " = " << nIter->second << "\n";
		}

		file.close();
	}
}
