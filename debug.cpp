
#include "base.hpp"

extern "C"
{

int printf_TODO(const char * format, ...)
{
	CHECK_INIT;

	int ret = 0;
	char buf[1024 + strlen(format)];
	va_list args;
	
	sprintf(buf, "[ TODO ] %s", format);

	va_start(args, format);
	ret = vprintf(buf, args);
	va_end(args);

	return ret;
}

void print_count_values_in_buf(const uint16_t * buf, const unsigned height, const unsigned width)
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

void print_buf_checksum(const uint8_t * buf, const unsigned size)
{
	CHECK_INIT;

	uint64_t sum = 0;
	unsigned v;

	for(v = 0; v < size; v++)
		sum += buf[v];

	printf_TODO("Checksum = %u\n", sum);
}

#ifndef __MINGW32__

void print_memory_usage()
{
	CHECK_INIT;

	struct mallinfo info = mallinfo();

	printf_TODO("bytes = %d\n", info.uordblks);
}

#endif

}

