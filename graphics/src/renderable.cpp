#include"../include/graphics/renderable.h"

#include"../include/graphics/graphics.h"

void bear::graphics::Renderable::setPosition(core::Vector2f & a_P)
{
	m_Position = a_P;
}

void bear::graphics::Renderable::setColor(core::Color & a_C)
{
	m_Color = a_C;
}

const bear::core::Vector2f bear::graphics::Renderable::getPosition()
{
	return m_Position;
}

const bear::core::Color bear::graphics::Renderable::getColor()
{
	return m_Color;
}