
#ifndef AMV_EXCEPTION_HPP
#define AMV_EXCEPTION_HPP

#ifdef WITH_OPENGL

	#define throw_ \
	{\
		fprintf(stderr, "[Exception] File %s, line %d, GL message 0x%X\n", __FILE__, __LINE__, glGetError());\
		throw 1;\
	};

#else

	#define throw_ \
	{\
		fprintf(stderr, "[Exception] File %s, line %d\n", __FILE__, __LINE__);\
		throw 1;\
	};

#endif

#define throw_if(condition) \
{\
	if((condition))\
		throw_;\
}

#define throw_null(pointer) \
	throw_if((pointer) == NULL)

#endif

