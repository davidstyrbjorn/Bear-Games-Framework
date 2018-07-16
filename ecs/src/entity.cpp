#include "../include/ecs/entity.h"

#include"../include/ecs/rectangle_component.h"

using namespace bear;

bear::ecs::Entity::Entity(std::string a_ID) : m_ID(a_ID)
{
	m_ComponentList[0] = ecs::RectangleComponent(core::Color::White());
}

std::string bear::ecs::Entity::getID()
{
	return m_ID;
}

void bear::ecs::Entity::setID(std::string a_ID)
{
	m_ID = a_ID;
}
