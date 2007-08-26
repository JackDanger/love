/**
* @file platform.h
* @author Anders Ruud
* @date 2007-08-17
* @brief Contains function declarations for platform code.
**/

namespace love
{

	/**
	* @brief Readies devices, libraries, etc. (Assigns all needed "modules" to love::core).
	* @param argc Number of command like arguments.
	* @param argv A pointer to the array of command line arguments.
	**/
	extern int platform_init(int argc, char* argv[]);

	/**
	* @brief This method contains the main program loop.
	* Once called, it will not finish before the end of the program.
	**/
	extern int platform_loop();

	/**
	* @brief Causes the program to exit.
	**/
	extern void platform_quit();

}
