#include"../include/graphics/renderable.h"

#include"../include/graphics/image.h"
#include"../include/graphics/texture.h"

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Renderable::Renderable(Image& a_Image) :
	m_Type(bear::graphics::renderable_type::Sprite)
{
	m_Texture = new Texture(a_Image);
	m_Transform.m_Size = core::Vector2f(a_Image.m_ImageSize.x, a_Image.m_ImageSize.y);
}

bear::graphics::Renderable::~Renderable()
{

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
	return m_Texture->getTextureID();
}

void bear::graphics::Renderable::setTextureImage(const Image & a_Image)
{
	
}