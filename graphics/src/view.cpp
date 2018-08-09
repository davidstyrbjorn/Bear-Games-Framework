#include"../include/graphics/view.h"

#include"../include/graphics/graphics.h"

#include<window\GLFW_window.h>

using namespace bear;
using namespace bear::graphics;

View::View()
{
	m_WorldPosition = core::Vector2f(0, 0);
	m_ViewMatrix = core::Matrix4x4::Translation(core::Vector3f(0, 0, 0));
}

View::View(core::Vector2f a_Position)
{
	m_WorldPosition = a_Position;
	m_ViewMatrix = core::Matrix4x4::Translation(core::Vector3f(m_WorldPosition.x, m_WorldPosition.y, 0));
}

void View::setPosition(core::Vector2f a_Position)
{
	m_WorldPosition = a_Position;
	_update_matrix();
}

void bear::graphics::View::translate(core::Vector2f a_Translation)
{
	m_WorldPosition += a_Translation;
	_update_matrix();
}

core::Matrix4x4& View::getViewMatrix()
{
	return m_ViewMatrix;
}

core::Vector2f bear::graphics::View::getPosition()
{
	return m_WorldPosition;
}

void View::_update_matrix()
{
	m_ViewMatrix = core::Matrix4x4::Translation(core::Vector3f(m_WorldPosition.x, m_WorldPosition.y, 0));
}