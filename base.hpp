
#ifndef AMV_BASE_HPP
#define AMV_BASE_HPP

#ifdef IS_BUILD

	#include <cstdio>
	#include <cstdarg>
	#include <cstdint>
	#include <cstring>
	#include <sstream>
	#include <map>
	#include <memory>

	#ifndef __MINGW32__

		#include <malloc.h>

	#endif

	#include "debug.hpp"
	#include "exception.hpp"
	#include "3dpart/rapidxml/rapidxml_print.hpp"
	#include "3dpart/rapidxml/rapidxml.hpp"

	using namespace std;
	using namespace rapidxml;

	// ############################################################################ 

	#define CHECK_INIT\
		throw_if(! is_init());

	bool is_init();

#endif

extern "C"
{
	void amv_init();
	void amv_destroy();
};

#endif

