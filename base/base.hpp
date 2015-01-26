
#ifndef AMV_BASE_HPP
#define AMV_BASE_HPP

#include <cstdio>
#include <cstring>
#include <memory>
#include <cerrno>
#include <cstdarg>

namespace amv
{
	;
}

#ifdef IS_BUILD

	#include "3dpart/rapidxml/rapidxml_print.hpp"
	#include "3dpart/rapidxml/rapidxml.hpp"

	#include "debug/debug.hpp"

	using namespace std;
	using namespace rapidxml;
	using namespace amv;

#endif

#endif

