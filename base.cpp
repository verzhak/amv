
#include "base.hpp"

bool __is_init;

extern "C"
{

void amv_init()
{
	if(! __is_init)
		__is_init = true;
}

void amv_destroy()
{
	CHECK_INIT;

	__is_init = false;
}

}

#ifdef IS_BUILD

bool is_init()
{
	return __is_init;
}

#endif

