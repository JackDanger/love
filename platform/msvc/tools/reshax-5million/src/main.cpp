#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		resources_cpp.open("Resources.cpp");
		resources_h.open("Resources.h");
		for (int i = 1; i < argc; i++)
		{
			// use boost::filesystem to list all the files (in v2 maybe)
			load(argv[i]);
		}
		resources_cpp.close();
		resources_h.close();
	}

	else
		printf("ResHax-5Million v1.0\n- made with LÖVE ^.^\n\nUsage: reshax-5million [file1] [file2] [and so on...]\n");
}

void load(string file)
{
	ifstream fs (file.c_str(), fstream::in | fstream::binary | fstream::ate);
	if (fs.is_open() && fs.good())
	{
		printf("Haxing %s", file.c_str());
		
		int size = (int)fs.tellg();
		char buff[size];
		fs.seekg(0, ios::beg);
		fs.read(buff, size);
#ifndef WIN32
		struct stat fstat;
		stat(file.c_str(), &fstat);
		if (!S_ISDIR(fstat.st_mode))
			write(file, size, buff);
		else
			printf(" FAIL cuz DIR\n");
#else
		write(file, size, buff);
#endif
		fs.close();
	}
	else
		printf("Hax does not liek '%s'\n", file.c_str());
}

void write(string file, int size, char *data)
{
	char buffer[8];
	size--;

	// removes directory
	size_t found;
	found = file.find_last_of('/');
	if (found != string::npos)
		file = file.substr(found + 1);

	// replaces dashes and dots (in UNIX only)
#ifndef WIN32
	found = file.find_first_of(" !\"#$%&'()*+,-.@[]", 0);
	while (found != string::npos)
	{
		file[found] = '_';
		found = file.find_first_of(" !\"#$%&'()*+,-.@[]", found);
	}
#endif

	string var = "char ";
	var += file;
	var += "[] = {";
	resources_cpp << var.c_str();
	for (int i = 0; i < size; i++)
	{
		sprintf(buffer, "%d,", data[i]);
		resources_cpp << buffer;
		if (i % 30 == 0)
			resources_cpp << "\n\t";
	}
	sprintf(buffer, "%d};\n\n", data[size]);
	resources_cpp << buffer;

	var = "extern char ";
	var += file;
	var += "[];\n";
	resources_h << var;

	printf(" is haxed\n");
}
