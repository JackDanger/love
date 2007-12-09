#include "Configuration.h"
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
	Configuration::Configuration(string filepath) : filepath(filepath)
	{
	}

	Configuration::Configuration(pAbstractFile file) : Resource(file), filepath("")
	{
	}

	Configuration::~Configuration()
	{
		unload();
	}

	int Configuration::load()
	{
		string temp, key, value;
		int index ,line;

		istream * ifs;

		if(filepath != "")
		{
			ifs = new ifstream (filepath.c_str());
		}
		else
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

				if(exists(key) && core->isVerbose())
					core->printf("ConfigLoader: Overwriting config entry '%s'.\n", key.c_str());
				data[key] = value;
			}
		}

		return LOVE_OK;
	}

	void Configuration::unload()
	{
		data.clear();
	}

	string Configuration::getString(string key)
	{
		if(isString(key))
			return data[key].substr(1, data[key].size() - 2); // to remove the quotation marks
		else
			return "";
	}

	bool Configuration::getBool(string key)
	{
		if(isBool(key))
			return data[key].compare("true") == 0 ? true : false;
		else
			return false;
	}

	float Configuration::getFloat(string key)
	{
		if(isFloat(key))
			return (float)atof(data[key].c_str());
		else
			return 0.0f;
	}
	
	int Configuration::getInt(string key)
	{
		if(isInt(key))
			return atoi(data[key].c_str());
		else
			return 0;
	}

	bool Configuration::isString(string key)
	{
		if(data.count(key) == 0)
			return false;

		if((int)data[key].find_first_of('"', 0) == 0 && data[key].find_last_of('"', data[key].size() - 1) == data[key].size() - 1)
			return true;
		else
			return false;
	}

	bool Configuration::isBool(string key)
	{
		if(data.count(key) == 0)
			return false;

		if(data[key].compare("true") == 0 || data[key].compare("false") == 0 )
			return true;
		else
			return false;
	}

	bool Configuration::isFloat(string key)
	{
		if(data.count(key) == 0)
			return false;
		
		if(sprintf(buffer, "%f", data[key]) != -1)
			return true;
		else
			return false;
	}

	bool Configuration::isInt(string key)
	{
		if(data.count(key) == 0)
			return false;
		
		if(sprintf(buffer, "%d", data[key]) != -1)
			return true;
		else
			return false;
	}

	bool Configuration::exists(string key)
	{
		if(data.count(key) != 0)
			return true;
		else
			return false;
	}

	void Configuration::addString(string key, string value)
	{
		sprintf(buffer, "\"%s\"", value.c_str());
		data[key] = buffer;
	}

	void Configuration::add(string key, string value)
	{
		addString(key, value);
	}

	void Configuration::addBool(string key, bool value)
	{
		if(value)
			data[key] = "true";
		else
			data[key] = "false";
	}

	void Configuration::add(string key, bool value)
	{
		addBool(key, value);
	}

	void Configuration::addFloat(string key, float value)
	{
		sprintf(buffer, "%f", value);
		data[key] = string(buffer);
	}

	void Configuration::add(string key, float value)
	{
		addFloat(key, value);
	}

	void Configuration::addInt(string key, int value)
	{
		sprintf(buffer, "%d", value);
		data[key] = string(buffer);
	}

	void Configuration::add(string key, int value)
	{
		addInt(key, value);
	}

	void Configuration::write()
	{
		ofstream file(filepath.c_str(), ios::trunc);
		if(!file)
		{
			core->error("ConfigLoader: ERROR! Could not write to file '%s'.\n", filepath.c_str());
			//printf("Config Loader: ERROR! Could not write to file '%s'.\n", filepath.c_str());
			return;
		}

		map<string, string>::iterator sIter;
		for(sIter = data.begin(); sIter != data.end(); sIter++)
		{
			file << sIter->first << " = " << sIter->second << "\n";
		}

		file.close();
	}
}
