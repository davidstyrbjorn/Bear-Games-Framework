#pragma once

#include<core\vector2.h>

namespace bear { namespace graphics {

	enum image_format {
		RGB = 0x1907, // GL_RGB
		RGBA = 0x1908 // GL_RGBA

	};

	struct Image {
		core::Vector2i m_ImageSize;
		void* m_ImageData;
		image_format m_Format;

		Image(std::string a_ImagePath);
		~Image();
	};

} }