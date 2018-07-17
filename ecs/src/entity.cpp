#include "../include/ecs/entity.h"

#include"../include/ecs/rectangle_component.h"

using namespace bear;

bear::ecs::Entity::Entity(std::string a_ID) : m_ID(a_ID)
{
	m_ComponentList[0] = { ecs::RectangleComponent(core::Color::White()), false };
}

bear::ecs::Entity::~Entity()
{

}

void bear::ecs::Entity::update()
{

}

bool bear::ecs::Entity::addComponent(component_types a_Type)
{
	if (a_Type == component_types::RENDERABLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT].m_IsActive == false) {
		m_ComponentList[component_types::RENDERABLE_COMPONENT].m_IsActive = true;
		m_ComponentList[component_types::RENDERABLE_COMPONENT].m_Component.reset();
	}

	return true;
}

bear::ecs::Component* bear::ecs::Entity::getComponent(component_types a_Type)
{
	return &m_ComponentList[0].m_Component;
	if (a_Type == component_types::RENDERABLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT].m_IsActive == true) {
		return static_cast<RectangleComponent*>(&m_ComponentList[component_types::RENDERABLE_COMPONENT].m_Component);
	}

	return nullptr;
}

std::string bear::ecs::Entity::getID()
{
	return m_ID;
}

void bear::ecs::Entity::setID(std::string a_ID)
{
	m_ID = a_ID;
}
