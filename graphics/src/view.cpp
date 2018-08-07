#include"../include/graphics/view.h"

using namespace bear;
using namespace bear::graphics;

View::View()
{
	//m_ViewMatrix = core::Matrix4x4::Orthographic()
}

View::View(core::Vector2f a_Position)
{

}

void View::setPosition(core::Vector2f a_Position)
{

}

core::Matrix4x4& View::getViewMatrix()
{
	return m_ViewMatrix;
}

void View::_update_matrix()
{

}