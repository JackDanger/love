#include <fstream>
#include <map>
#include <sys/stat.h>

std::ofstream resources_cpp, resources_h;

void load(std::string file);
void write(std::string file, int size, char *data);
