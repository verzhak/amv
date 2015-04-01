
#ifndef AMV_DEBUG_HPP
#define AMV_DEBUG_HPP

#include <cstdio>
#include <cstring>

namespace amv
{

	int printf_prefix(const std::string prefix, const std::string fname, const unsigned lnum, const char * format, ...);
	int printf_TODO(const char * format, ...);

	/*
	 * TODO Удалить?
	void print_count_values_in_buf(const std::uint16_t * buf, const unsigned height, const unsigned width);
	void print_buf_checksum(const std::uint8_t * buf, const unsigned size);

	#ifndef __MINGW32__

		void print_memory_usage();

	#endif
	*/

}

#ifdef WITH_OPENGL

	#define __condition glGetError()
	#define __format "gl: %u"
	#define __param glGetError()

#else

	#define __condition true
	#define __format ""
	#define __param 0

#endif

#define DEBUG amv::printf_prefix("Debug", __FILE__, __LINE__, __format, __param);

#define DEBUG_ONLY_ERROR \
{\
	if(__condition || std::errno)\
		amv::printf_prefix("Debug", __FILE__, __LINE__, __format, __param);\
}

#define throw_ \
{\
	amv::printf_prefix("Exception", __FILE__, __LINE__, __format, __param);\
	throw 1;\
};

#define throw_if(condition) \
{\
	if((condition))\
		throw_;\
}

#define throw_null(pointer) \
	throw_if((pointer) == nullptr)

#endif

