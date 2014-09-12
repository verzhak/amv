
#ifndef AMV_BMP_HPP
#define AMV_BMP_HPP

#include <cstdint>
#include <string>
#include <memory>

extern "C"
{
	void load_bmp(std::string fname, std::shared_ptr<std::uint8_t> & img, unsigned & height, unsigned & width, unsigned & channels);
	void save_bmp(std::string fname, const std::shared_ptr<std::uint8_t> & img, const unsigned height, const unsigned width, const unsigned channels);
};

#endif

