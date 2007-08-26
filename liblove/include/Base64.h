

#include <string>
using std::string;

namespace love 
{

	//*********************************************************************
	//* C_Base64 - a simple base64 encoder and decoder.
	//*
	//*     Copyright (c) 1999, Bob Withers - bwit@pobox.com
	//*
	//* This code may be freely used for any purpose, either personal
	//* or commercial, provided the authors copyright notice remains
	//* intact.
	//*********************************************************************

	#ifndef Base64_H
	#define Base64_H

	class Base64
	{
	public:
		static string encode(string data);
		static string decode(string data);
	};

	#endif


} // love
