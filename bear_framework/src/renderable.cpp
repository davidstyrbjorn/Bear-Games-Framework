#include"../include/graphics/renderable.h"

#include"../include/graphics/image.h"
#include"../include/graphics/texture.h"
#include"../include/memory/resource_manager.h"

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Renderable::Renderable(const std::string& a_TextureName) :
	m_Type(bear::graphics::renderable_type::Sprite),
	m_Color(core::Color::White()),
	m_TextureName(a_TextureName)
{
	Texture* texture = ResourceManager::Instance()->GetTexture(m_TextureName);
	m_Transform.m_Size = core::Vector2f(texture->getTextureSize().x, texture->getTextureSize().y);
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