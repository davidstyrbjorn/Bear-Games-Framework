#include"../include/graphics/image.h"

#include"../include/core/file_utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bear::graphics::Image::Image(void * a_ImageData, core::Vector2i a_ImageSize, image_format a_Format)
{
	m_ImageData = a_ImageData;
	m_ImageSize = a_ImageSize;
	m_Format = a_Format;
}

bear::graphics::Image::Image(std::string a_ImagePath, image_format a_Format)
{
	// Load image using stb
	int stbiFormat = 0;
	if (a_Format == image_format::RGBA) {
		stbiFormat = STBI_rgb_alpha;
	}
	else {
		stbiFormat = STBI_rgb;
	}

	const char* x = a_ImagePath.c_str();
	m_ImageData = stbi_load(x, &m_ImageSize.x, &m_ImageSize.y, nullptr, 0);
}

bear::graphics::Image::~Image()
{
	stbi_image_free(m_ImageData);
}
