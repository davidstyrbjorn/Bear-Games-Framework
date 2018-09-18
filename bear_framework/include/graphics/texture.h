#pragma once

#include"../core/vector2.h"
#include"image.h"

namespace bear { namespace graphics { 

	class Texture {
	private:
		unsigned int m_TBO;

	public:
		Texture(Image& a_Image);
		Texture(void *a_Data, core::Vector2i a_Size, image_format a_Format);
		Texture();
		~Texture();

		void setData(Image& a_Image);
		void bind();
		void unbind();
		int getTextureID();
	};

} } 