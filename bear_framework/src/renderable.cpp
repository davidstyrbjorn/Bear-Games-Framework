#include"../include/graphics/renderable.h"

#include"../include/graphics/image.h"

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Renderable::Renderable(std::string a_ImagePath) :
	m_Type(bear::graphics::renderable_type::Sprite)
{
	glGenTextures(1, &m_TBO);
	glBindTexture(GL_TEXTURE_2D, m_TBO);

	Image image(a_ImagePath);

	glTexImage2D(GL_TEXTURE_2D, 0, image.m_Format, image.m_ImageSize.x, image.m_ImageSize.y, 0, image.m_Format, GL_UNSIGNED_BYTE, image.m_ImageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_Transform.m_Size = core::Vector2f(image.m_ImageSize.x, image.m_ImageSize.y);
}

bear::graphics::Renderable::~Renderable()
{
	if (glIsTexture(m_TBO)) {
		glDeleteTextures(1, &m_TBO);
	}
}

void bear::graphics::Renderable::setColor(core::Color & a_C)
{
	m_Color = a_C;
}

const bear::core::Color bear::graphics::Renderable::getColor()
{
	return m_Color;
}

bear::graphics::Transform & bear::graphics::Renderable::transform()
{
	return m_Transform;
}

const bear::graphics::renderable_type bear::graphics::Renderable::getType()
{
	return m_Type;
}

void bear::graphics::Renderable::setType(renderable_type a_Type)
{
	m_Type = a_Type;
}

int bear::graphics::Renderable::getTextureID()
{
	return m_TBO;
}

void bear::graphics::Renderable::setTextureImage(const Image & a_Image)
{
	
}