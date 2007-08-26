/**
* @file lualove_types_looup.h
* @brief Lookup table between SWIG types and LOVE types.
* @date 2006-11-26
* @author
**/

#ifndef LOVE_LUALOVE_TYPES_LOOKUP_H
#define LOVE_LUALOVE_TYPES_LOOKUP_H

namespace love
{
	
	static int * lualove_lookup_types;

	void lualove_create_lookup();
	void lualove_clean_lookup();
	int lualove_get_type(int type);

} // love

#endif
