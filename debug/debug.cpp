
#include "base/base.hpp"
#include "debug/debug.hpp"

#define throw__ fprintf(stderr, "[Exception] File %s, line %d\n", __FILE__, __LINE__);

#define throw_if_(condition) \
{\
	if((condition))\
		throw__;\
}

#define throw_null_(pointer) \
	throw_if_((pointer) == nullptr)

int amv::printf_prefix(const string prefix, const string fname, const unsigned lnum, const char * format, ...)
{
	int ret = 0;
	const string err_msg = strerror(errno);
	const unsigned buf_size = prefix.size() + fname.size() + to_string(lnum).size() + err_msg.size() + strlen(format) + 4096;
	shared_ptr<char> buf(new char[buf_size], default_delete<char[]>());
	char * p_buf = buf.get();
	va_list args;

	throw_null_(p_buf);
	sprintf(p_buf, "[ %s ] File: %s, line: %u, errno: %s, info: [ %s ]", prefix.c_str(), fname.c_str(), lnum, err_msg.c_str(), format);

	va_start(args, format);
	ret = vprintf(p_buf, args);
	va_end(args);

	return ret;
}

int amv::printf_TODO(const char * format, ...)
{
	int ret = 0;
	shared_ptr<char> buf(new char[1024 + strlen(format)], default_delete<char[]>());
	char * p_buf = buf.get();
	va_list args;

	throw_null_(p_buf);
	sprintf(p_buf, "[ TODO ] %s", format);

	va_start(args, format);
	ret = vprintf(p_buf, args);
	va_end(args);

	return ret;
}

/*
void amv::print_count_values_in_buf(const uint16_t * buf, const unsigned height, const unsigned width)
{
	CHECK_INIT;

	unsigned v, u, t;
	map<unsigned, unsigned> num;

	for(v = 0, t = 0; v < height; v++)
		for(u = 0; u < width; u++, t++)
		{
			const unsigned ind = buf[t];

			num[ind] = (num.count(ind) ? num[ind] : 0) + 1;
		}

	for(auto & elem : num)
		printf_TODO("0x%X = %u\n", elem.first, elem.second);
}

void amv::print_buf_checksum(const uint8_t * buf, const unsigned size)
{
	CHECK_INIT;

	uint64_t sum = 0;
	unsigned v;

	for(v = 0; v < size; v++)
		sum += buf[v];

	printf_TODO("Checksum = %u\n", sum);
}

#ifndef __MINGW32__

void amv::print_memory_usage()
{
	CHECK_INIT;

	struct mallinfo info = mallinfo();

	printf_TODO("bytes = %d\n", info.uordblks);
}

#endif
*/

