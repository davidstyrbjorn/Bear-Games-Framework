#include "../include/ecs/entity.h"

#include"../include/ecs/bear_components/rectangle_component.h"
#include"../include/ecs/bear_components/transform_component.h"

using namespace bear;

bear::ecs::Entity::Entity(std::string a_ID) : m_ID(a_ID)
{
	m_ComponentList[component_types::TRANSFORM_COMPONENT] = { new ecs::TransformComponent(), true };
	m_ComponentList[component_types::RENDERABLE_COMPONENT] = { new ecs::RectangleComponent(core::Color::White()), false };
}

bear::ecs::Entity::~Entity()
{
	for (int i = 0; i < COMPONENT_COUNT; i++) {
		delete m_ComponentList[i].m_Component;
	}
}

void bear::ecs::Entity::update()
{
	for (int i = 0; i < COMPONENT_COUNT; i++) {
		if (m_ComponentList[i].m_IsPossesed)
		{
			m_ComponentList[i].m_Component->update();
		}
	}
}

bool bear::ecs::Entity::addComponent(component_types a_Type)
{
	if (a_Type == component_types::RENDERABLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT].m_IsPossesed == false) {
		m_ComponentList[component_types::RENDERABLE_COMPONENT].m_IsPossesed = true;
		m_ComponentList[component_types::RENDERABLE_COMPONENT].m_Component->reset();
	}

	return true;
}

inline bear::ecs::TransformComponent * bear::ecs::Entity::transform()
{
	return static_cast<TransformComponent*>(m_ComponentList[component_types::TRANSFORM_COMPONENT].m_Component);
}

std::string bear::ecs::Entity::getID()
{
	return m_ID;
}

void bear::ecs::Entity::setID(std::string a_ID)
{
	m_ID = a_ID;
}
