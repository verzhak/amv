
#ifndef AMV_DEBUG_HPP
#define AMV_DEBUG_HPP

// Отладочная печать

#include <cstdint>

extern "C"
{
	int printf_TODO(const char * format, ...);
	void print_count_values_in_buf(const std::uint16_t * buf, const unsigned height, const unsigned width);
	void print_buf_checksum(const std::uint8_t * buf, const unsigned size);

	#ifndef __MINGW32__

		void print_memory_usage();

	#endif
};

// ############################################################################ 
// Отладка с маркерами

#ifdef WITH_OPENGL

	#define DEBUG printf_TODO("debug = file: %s, line: %u, gl: 0x%X\n", __FILE__, __LINE__, glGetError());

	#define DEBUG_ONLY_ERROR \
	{\
		int error_index = glGetError();\
		\
		if(error_index)\
			printf_TODO("debug = file: %s, line: %u, gl: 0x%X\n", __FILE__, __LINE__, error_index);\
	}

#else

	#define DEBUG printf_TODO("debug = file: %s, line: %u\n", __FILE__, __LINE__);
	#define DEBUG_ONLY_ERROR DEBUG

#endif

#endif

