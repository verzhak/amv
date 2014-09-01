
#ifndef AMV_IMAGE_HPP
#define AMV_IMAGE_HPP

#include <cstdint>
#include <string>
#include <memory>

extern "C"
{
	void load_image(std::string fname, std::shared_ptr<std::uint8_t> & img, unsigned & height, unsigned & width, unsigned & channels);
	void save_image(std::string fname, const std::shared_ptr<std::uint8_t> & img, const unsigned height, const unsigned width, const unsigned channels);
};

#endif

