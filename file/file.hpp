
#ifndef AMV_FILE_HPP
#define AMV_FILE_HPP

#include <cstdio>
#include <cstdint>
#include <memory>
#include <endian.h>

enum EFileMode
{
	EFileModeBinaryRead, EFileModeBinaryWrite
};

class CFile
{
	std::FILE * fl;
	const EFileMode __mode;

	public:

		CFile(const std::string fname, const EFileMode mode);
		~CFile();

		void read(void * buf, const size_t size);
		std::shared_ptr<std::uint8_t> read_all();
		void write(const void * buf, const size_t size);
		void seek(const std::uint32_t offset);
		long offset();
		unsigned size();

		inline void operator()(void * buf, const size_t size) { read(buf, size); };

		#define PACK(__TYPE, fun)\
		else if(typeid(TYPE) == typeid(__TYPE))\
		{\
			for(v = 0; v < num; v++)\
				buf[v] = fun(buf[v]);\
		}

		#define PACK_REAL(__TYPE, __D_TYPE, fun)\
		else if(typeid(TYPE) == typeid(__TYPE))\
		{\
			__D_TYPE val;\
			\
			for(v = 0; v < num; v++)\
			{\
				val = fun(* (__D_TYPE *) (buf + v));\
				buf[v] = * (TYPE *) & val;\
			}\
		}

		template<typename TYPE>
			static void pack(TYPE * buf, const unsigned num = 1)
			{
				#ifndef __MINGW32__

					unsigned v;

					if(typeid(TYPE) == typeid(std::uint8_t))
					{
						;
					}
					PACK(std::uint16_t, htole16)
					PACK(std::uint32_t, htole32)
					PACK(std::uint64_t, htole64)
					PACK_REAL(float, std::uint32_t, htole32)
					PACK_REAL(double, std::uint64_t, htole64)
					else
					{
						throw_;
					}

				#endif
			}

		template<typename TYPE>
			static void unpack(TYPE * buf, const unsigned num = 1)
			{
				CFile::pack<TYPE>(buf, num);
			}

		template<typename TYPE>
			void read_unpack(TYPE * buf, const unsigned num = 1)
			{
				read((void *) buf, sizeof(TYPE) * num);
				CFile::unpack<TYPE>(buf, num);
			}

		template<typename TYPE>
			void write_pack(const TYPE * buf, const unsigned num = 1)
			{
				const unsigned size = sizeof(TYPE) * num;
				std::shared_ptr<TYPE> __buf;
				TYPE * __p_buf;

				__buf.reset(new TYPE[num], std::default_delete<TYPE[]>());
				throw_null(__p_buf = __buf.get());

				memcpy(__p_buf, buf, size);
				CFile::pack<TYPE>(__p_buf, num);
				write((void *) __p_buf, size);
			}
};

#endif

