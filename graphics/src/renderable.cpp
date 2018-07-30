#include"../include/graphics/renderable.h"

#include"../include/graphics/image.h"

bear::graphics::Renderable::Renderable(std::string a_ImagePath) :
	m_Type(bear::graphics::renderable_type::Sprite)
{
	m_Image = new Image(a_ImagePath);
	m_Transform.m_Size = core::Vector2f(m_Image->m_ImageSize.x, m_Image->m_ImageSize.y);
}

bear::graphics::Renderable::~Renderable()
{
	delete m_Image;
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

bear::graphics::Image * bear::graphics::Renderable::getImage()
{
	return nullptr;
}
