
#include "base.hpp"
#include "image/bmp.hpp"
#include "file/file.hpp"

#define WORD uint16_t
#define DWORD uint32_t

struct __attribute__((packed)) BITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
};

struct __attribute__((packed)) BITMAPINFOHEADER
{
	DWORD biSize;
	DWORD biWidth;
	DWORD biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	DWORD biXPelsPerMeter;
	DWORD biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
};

struct BITMAPHEADER
{
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;
};

void pack_header(BITMAPHEADER & header)
{
	CFile::pack<WORD>(& header.bmfHeader.bfType);
	CFile::pack<DWORD>(& header.bmfHeader.bfSize);
	CFile::pack<WORD>(& header.bmfHeader.bfReserved1);
	CFile::pack<WORD>(& header.bmfHeader.bfReserved2);
	CFile::pack<DWORD>(& header.bmfHeader.bfOffBits);

	CFile::pack<DWORD>(& header.bmiHeader.biSize);
	CFile::pack<DWORD>(& header.bmiHeader.biWidth);
	CFile::pack<DWORD>(& header.bmiHeader.biHeight);
	CFile::pack<WORD>(& header.bmiHeader.biPlanes);
	CFile::pack<WORD>(& header.bmiHeader.biBitCount);
	CFile::pack<DWORD>(& header.bmiHeader.biCompression);
	CFile::pack<DWORD>(& header.bmiHeader.biSizeImage);
	CFile::pack<DWORD>(& header.bmiHeader.biXPelsPerMeter);
	CFile::pack<DWORD>(& header.bmiHeader.biYPelsPerMeter);
	CFile::pack<DWORD>(& header.bmiHeader.biClrUsed);
	CFile::pack<DWORD>(& header.bmiHeader.biClrImportant);
}

void unpack_header(BITMAPHEADER & header)
{
	CFile::unpack<WORD>(& header.bmfHeader.bfType);
	CFile::unpack<DWORD>(& header.bmfHeader.bfSize);
	CFile::unpack<WORD>(& header.bmfHeader.bfReserved1);
	CFile::unpack<WORD>(& header.bmfHeader.bfReserved2);
	CFile::unpack<DWORD>(& header.bmfHeader.bfOffBits);

	CFile::unpack<DWORD>(& header.bmiHeader.biSize);
	CFile::unpack<DWORD>(& header.bmiHeader.biWidth);
	CFile::unpack<DWORD>(& header.bmiHeader.biHeight);
	CFile::unpack<WORD>(& header.bmiHeader.biPlanes);
	CFile::unpack<WORD>(& header.bmiHeader.biBitCount);
	CFile::unpack<DWORD>(& header.bmiHeader.biCompression);
	CFile::unpack<DWORD>(& header.bmiHeader.biSizeImage);
	CFile::unpack<DWORD>(& header.bmiHeader.biXPelsPerMeter);
	CFile::unpack<DWORD>(& header.bmiHeader.biYPelsPerMeter);
	CFile::unpack<DWORD>(& header.bmiHeader.biClrUsed);
	CFile::unpack<DWORD>(& header.bmiHeader.biClrImportant);
}

void load_bmp(string fname, shared_ptr<uint8_t> & img, unsigned & height, unsigned & width, unsigned & channels)
{
	uint8_t * p_img, * p_buf;
	unsigned v, img_size, file_line_width, bits_per_sample;
	shared_ptr<uint8_t> buf;
	BITMAPHEADER header;
	CFile fl(fname, EFileModeBinaryRead);

	fl.read(& header, sizeof(BITMAPHEADER));
	unpack_header(header);

	bits_per_sample = header.bmiHeader.biBitCount;

	throw_if(header.bmfHeader.bfType != 0x4D42 || bits_per_sample != 24 || header.bmiHeader.biPlanes != 1 || header.bmiHeader.biCompression);

	height = header.bmiHeader.biHeight;
	width = header.bmiHeader.biWidth;
	channels = 3;
	file_line_width = width * (bits_per_sample / 8);
	file_line_width += (file_line_width & 3) ? 4 - (file_line_width & 3) : 0;

	img_size = header.bmfHeader.bfSize - header.bmfHeader.bfOffBits;
	img.reset(new uint8_t[img_size], std::default_delete<uint8_t[]>());
	buf.reset(new uint8_t[img_size], std::default_delete<uint8_t[]>());
	throw_null(p_img = img.get());
	throw_null(p_buf = buf.get());
	p_img += file_line_width * (height - 1);

	fl.seek(header.bmfHeader.bfOffBits);
	fl.read_unpack<uint8_t>(p_buf, img_size);

	for(v = 0; v < height; v++, p_buf += file_line_width, p_img -= file_line_width)
		memcpy(p_img, p_buf, file_line_width);
}

void save_bmp(string fname, const shared_ptr<uint8_t> & img, const unsigned height, const unsigned width, const unsigned channels)
{
	throw_if(channels != 3);

	unsigned v, img_size;
	unsigned file_line_width = width * 3;
	shared_ptr<uint8_t> buf;
	uint8_t * p_img, * p_buf;
	BITMAPHEADER header;
	CFile fl(fname, EFileModeBinaryWrite);

	if(file_line_width & 3)
		file_line_width += 4 - (file_line_width & 3);

	img_size = file_line_width * height;
	buf.reset(new uint8_t[img_size], std::default_delete<uint8_t[]>());
	throw_null(p_img = img.get());
	throw_null(p_buf = buf.get());
	p_buf += file_line_width * (height - 1);

	header.bmfHeader.bfType = 0x4D42;
	header.bmfHeader.bfOffBits = sizeof(BITMAPHEADER);
	header.bmfHeader.bfSize = header.bmfHeader.bfOffBits + img_size;
	header.bmfHeader.bfReserved1 = 0;
	header.bmfHeader.bfReserved2 = 0;

	header.bmiHeader.biSize = 40;
	header.bmiHeader.biWidth = width;
	header.bmiHeader.biHeight = height;
	header.bmiHeader.biPlanes = 1;
	header.bmiHeader.biBitCount = 24;
	header.bmiHeader.biCompression = 0;
	header.bmiHeader.biSizeImage = 0;
	header.bmiHeader.biXPelsPerMeter = 160;
	header.bmiHeader.biYPelsPerMeter = 160;
	header.bmiHeader.biClrUsed = 0;
	header.bmiHeader.biClrImportant = 0;

	pack_header(header);
	fl.write(& header, sizeof(BITMAPHEADER));

	for(v = 0; v < height; v++, p_img += file_line_width, p_buf -= file_line_width)
		memcpy(p_buf, p_img, file_line_width);

	fl.write_pack<uint8_t>(buf.get(), img_size);
}

