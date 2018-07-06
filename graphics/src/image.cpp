#include"../include/graphics/image.h"

#include<core\file_utility.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bear::graphics::Image::Image(std::string a_ImagePath)
{
	// Load image using stb
	int stbiFormat = 0;
	if (core::get_file_suffix(a_ImagePath) == ".png") {
		stbiFormat = STBI_rgb_alpha;
		m_Format = image_format::RGBA;
	}
	else {
		stbiFormat = STBI_rgb;
		m_Format = image_format::RGB;
	}

	const char* x = a_ImagePath.c_str();
	m_ImageData = stbi_load(x, &m_ImageSize.x, &m_ImageSize.y, nullptr, stbiFormat);
}

bear::graphics::Image::~Image()
{
	stbi_image_free(m_ImageData);
}
