
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

	#define amv_opengl_condition glGetError()
	#define amv_opengl_format "gl: %u"
	#define amv_opengl_param glGetError()

#else

	#define amv_opengl_condition true
	#define amv_opengl_format ""
	#define amv_opengl_param 0

#endif

#define DEBUG amv::printf_prefix("Debug", __FILE__, __LINE__, amv_opengl_format, amv_opengl_param);

#define DEBUG_ONLY_ERROR \
{\
	if(amv_opengl_condition || std::errno)\
		amv::printf_prefix("Debug", __FILE__, __LINE__, amv_opengl_format, amv_opengl_param);\
}

#define throw_ \
{\
	amv::printf_prefix("Exception", __FILE__, __LINE__, amv_opengl_format, amv_opengl_param);\
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

