
#ifndef AMV_BASE_HPP
#define AMV_BASE_HPP

#ifdef IS_BUILD

	#include <cstdio>
	#include <cstdarg>
	#include <cstdint>
	#include <opencv2/opencv.hpp>

	#ifndef __MINGW32__

		#include <malloc.h>

	#endif

	#include "debug.hpp"
	#include "exception.hpp"

	using namespace std;
	using namespace cv;

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

