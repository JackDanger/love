#include <love/Configuration.h>
#include <love/File.h>

using std::ifstream;
using std::istream;
using std::istringstream;
using std::map;
using std::ofstream;
using std::string;

/**
* @todo Get this out of here.
**/
//not a part of the actual class, just here to help
string trim(string s, string drop = " ")
{
	string r = s.erase(s.find_last_not_of(drop) + 1);
	return r.erase(0, r.find_first_not_of(drop));
}

namespace love
{

	Configuration::Configuration(pFile file) : Resource(file), filepath("")
	{
	}

	Configuration::~Configuration()
	{
		unload();
	}

	bool Configuration::load()
	{
		if(!file->load())
			return false;

		string temp, key, value;
		int index ,line;

		istream * ifs;

		if(filepath != "")
		{
			ifs = new ifstream (filepath.c_str());
		}
		else
		{
			string s(file->getData(), file->getSize());
			ifs = new istringstream(s);
		}

		
		if(!ifs)
		{
			printf("Configuration: ERROR! Could not read file '%s'.\n", filepath.c_str());
			return false;
		}

		line = 0;
		while(getline(*ifs, temp))
		{
			line++;
			index = (int)temp.find_first_of('=', 0);
			if(index == (int)string::npos)
				printf("Configuration (Line %d): Unrecognized command: \"%s\"\n", line, temp.c_str());
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

				// Overwriting is the preferred behaviour.
				//if(exists(key))
				//	printf("Configuration: Overwriting config entry '%s'.\n", key.c_str());
				data[key] = value;
			}
		}

		return true;
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
		
		// thnx tommy ^^
		for (string::const_iterator i = data[key].begin(); i != data[key].end(); i++)
			if (!isdigit(*i) && *i != ',' && *i != '.')
				return false;
		return true;
	}

	bool Configuration::isInt(string key)
	{
		if(data.count(key) == 0)
			return false;
		
		// thnx tommy ^^
		for (string::const_iterator i = data[key].begin(); i != data[key].end(); i++)
			if (!isdigit(*i))
				return false;
		return true;
	}

	bool Configuration::exists(string key)
	{
		if(data.count(key) != 0)
			return true;
		else
			return false;
	}

	void Configuration::add(string key, string value)
	{
		std::stringstream ss;
		ss << "\"" << value << "\"";
		data[key] = ss.str();
	}

	void Configuration::add(string key, bool value)
	{
		if(value)
			data[key] = "true";
		else
			data[key] = "false";
	}

	void Configuration::add(string key, float value)
	{
		std::stringstream ss;
		ss << value;
		data[key] = ss.str();
	}

	void Configuration::add(string key, int value)
	{
		std::stringstream ss;
		ss << value;
		data[key] = ss.str();
	}

	void Configuration::write()
	{
		ofstream file(filepath.c_str(), std::ios::trunc);
		if(!file)
		{
			printf("Configuration: ERROR! Could not write to file '%s'.\n", filepath.c_str());
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
