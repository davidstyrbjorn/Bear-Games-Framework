#include"../include/graphics/renderable.h"

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
