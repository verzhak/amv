
#include "all.hpp"

void load_save_image(const int argc, const char * argv[]);

int main(const int argc, const char * argv[])
{
	int ret = 0;

	amv_init();

	try
	{
		load_save_image(argc, argv);
	}
	catch(...)
	{
		ret = -1;
	}

	amv_destroy();

	return ret;
}

void load_save_image(const int argc, const char * argv[])
{
	unsigned height, width, channels;
	shared_ptr<uint8_t> img;

	throw_if(argc != 3);

	const string src_fname = argv[1];
	const string dst_fname = argv[2];

	load_image(src_fname, img, height, width, channels);
	save_image(dst_fname, img, height, width, channels);
}

