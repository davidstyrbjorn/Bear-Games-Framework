#include"../include/graphics/texture.h"

#define GLEW_STATIC
#include<GL\glew.h>

using namespace bear::graphics;

bear::graphics::Texture::Texture(Image & a_Image)
{
	glGenTextures(1, &m_TBO);
	setData(a_Image);
}

bear::graphics::Texture::Texture(void * a_Data, core::Vector2i a_Size, image_format a_Format)
{
	setData( { a_Data, a_Size, a_Format } );
}

bear::graphics::Texture::~Texture()
{
}

void bear::graphics::Texture::setData(Image & a_Image)
{
}
