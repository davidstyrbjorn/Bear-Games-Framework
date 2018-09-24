#include"../include/graphics/renderable.h"

#include"../include/graphics/image.h"
#include"../include/graphics/texture.h"
#include"../include/memory/resource_manager.h"

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Renderable::Renderable() :
	m_Transform(),
	m_Color(core::Color::White()),
	m_TextureName("")
{
}

void bear::graphics::Renderable::setTextureNameWData(const std::string & a_TextureName)
{
	m_TextureName = a_TextureName;
	Texture* texture = ResourceManager::Instance()->GetTexture(a_TextureName);
	m_Transform.m_Size = core::Vector2f(texture->getTextureSize().x, texture->getTextureSize().y); // Set renderable size to the texture size
}