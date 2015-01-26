
#include "base/base.hpp"
#include "file/file.hpp"

CFile::CFile(const string fname, const EFileMode mode) :
	fl(NULL), __mode(mode)
{
	string format;

	switch(mode)
	{
		case EFileModeBinaryRead:
		{
			format = "rb";
			
			break;
		}
		case EFileModeBinaryWrite:
		{
			format = "wb";

			break;
		}
	}

	throw_null(fl = fopen(fname.c_str(), format.c_str()));
}

CFile::~CFile()
{
	if(fl != NULL)
		fclose(fl);
}

void CFile::seek(const uint32_t offset)
{
	throw_if(fseek(fl, offset, SEEK_SET));
}

long CFile::offset()
{
	return ftell(fl);
}

unsigned CFile::size()
{
	const long pos = offset();

	throw_if(fseek(fl, 0, SEEK_END));

	const long sz = offset();

	throw_if(sz < 0);
	seek(pos);

	return sz;
}

void CFile::read(void * buf, const size_t size)
{
	throw_if(__mode != EFileModeBinaryRead);
	throw_if(fread(buf, size, 1, fl) != 1);
}

shared_ptr<uint8_t> CFile::read_all()
{
	const unsigned sz = size();
	shared_ptr<uint8_t> buf;

	if(sz)
	{
		buf.reset(new uint8_t[sz], default_delete<uint8_t[]>());
		read(buf.get(), sz);
	}

	return buf;
}

void CFile::write(const void * buf, const size_t size)
{
	throw_if(__mode != EFileModeBinaryWrite);
	throw_if(fwrite(buf, size, 1, fl) != 1);
}

