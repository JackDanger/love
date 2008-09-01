/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_ARG_H
#define LOVE_ARG_H

#include <cstring>
#include <string>

namespace love
{

	/**
	* Gets the filename of a game that should have been passed as a 
	* argument to love like so:
	* # love megagame.love					or
	* # love megagame						(folder)
	* Returns an empty string if there are no game argument.
	**/
	std::string get_arg_game(int argc, char* argv[]);

	/**
	* Gets the value to the right of a certain flag. Example:
	*
	* # love -b "C:/love"
	* string dir = get_arg(argc, argv, "-b"); // Would return C:/love.
	* 
	* Returns an empty string if the value does not exist.
	**/
	std::string get_arg(int argc, char* argv[], const std::string & attribute);

	/**
	* True if the string at the specified index is an option indicator. Example:
	* love -w 1024 ultragame.love
	* is_arg_option(argc, argv, 1) -> true // 1 = "-w"
	**/
	bool is_arg_option(int argc, char* argv[], int index);

	/**
	* Cheks if a string represents an absolute or relative path.
	**/
	bool is_arg_absolute(const std::string path);

	std::string get_leaf(const std::string full);

} // love

#endif // LOVE_ARG_H
