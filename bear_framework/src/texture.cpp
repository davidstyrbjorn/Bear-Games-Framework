#include"../include/graphics/texture.h"

#define GLEW_STATIC
#include<GL\glew.h>

using namespace bear::graphics;

bear::graphics::Texture::~Texture()
{
	glDeleteTextures(1, &m_TBO);
}

bear::graphics::Texture::Texture(Image & a_Image)
{
	// Genereate a texture
	glGenTextures(1, &m_TBO);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unbind();
	setData(a_Image);
}

bear::graphics::Texture::Texture(void * a_Data, core::Vector2i a_Size, image_format a_Format)
{
	// Generate a texture 
	glGenTextures(1, &m_TBO);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unbind();
	setData(Image(a_Data, a_Size, a_Format) );
}

bear::graphics::Texture::Texture()
{
	// Generate a texture and do nothing?
	glGenTextures(1, &m_TBO);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unbind();
}

void bear::graphics::Texture::setData(Image & a_Image)
{
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, a_Image.m_Format, a_Image.m_ImageSize.x, a_Image.m_ImageSize.y,
		0, a_Image.m_Format, GL_UNSIGNED_BYTE, a_Image.m_ImageData);
	unbind();
}

void bear::graphics::Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TBO);
}

void bear::graphics::Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int bear::graphics::Texture::getTextureID()
{
	return m_TBO;
}
