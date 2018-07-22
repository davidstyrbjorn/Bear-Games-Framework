#include "../include/ecs/entity.h"

#include"../include/ecs/bear_components/rectangle_component.h"
#include"../include/ecs/bear_components/triangle_component.h"
#include"../include/ecs/bear_components/sprite_component.h"

#include"../include/ecs/bear_components/transform_component.h"

using namespace bear;

bear::ecs::Entity::Entity(std::string a_ID) : m_ID(a_ID)
{
	m_ComponentList[component_types::TRANSFORM_COMPONENT] =  { new ecs::TransformComponent() };
	m_ComponentList[component_types::RENDERABLE_COMPONENT] = { nullptr };
}

bear::ecs::Entity::~Entity()
{
	// Delete bear components
	for (int i = 0; i < COMPONENT_COUNT; i++) {
		delete m_ComponentList[i];
	}
}

void bear::ecs::Entity::update()
{
	// Loop and update each bear component
	for (int i = 0; i < COMPONENT_COUNT; i++) {
		if (m_ComponentList[i] != nullptr)
		{
			m_ComponentList[i]->update();
		}
	}

	// Delete components that is to be removed
	while (!m_ComponentsToRemove.empty()) {
		component_types i = m_ComponentsToRemove.front();
		std::remove(m_ComponentList.begin(), m_ComponentList.end(), m_ComponentList[i]);
		m_ComponentsToRemove.pop_front();
	}
}

bool bear::ecs::Entity::addComponent(component_types a_Type)
{
	if (a_Type == component_types::RECTANGLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT] == nullptr) {
		m_ComponentList[component_types::RENDERABLE_COMPONENT] = (new RectangleComponent());
		m_ComponentList[component_types::RENDERABLE_COMPONENT]->init();
		return true;
	}
	else if (a_Type == component_types::TRIANGLE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT] == nullptr) {
		m_ComponentList[component_types::RENDERABLE_COMPONENT] = (new TriangleComponent());
		m_ComponentList[component_types::RENDERABLE_COMPONENT]->init();
		return true;
	}
	else if (a_Type == component_types::SPRITE_COMPONENT && m_ComponentList[component_types::RENDERABLE_COMPONENT] == nullptr)
	{
		m_ComponentList[component_types::RENDERABLE_COMPONENT] = (new SpriteComponent());
		m_ComponentList[component_types::RENDERABLE_COMPONENT]->init();
		return true;
	}

	return false;
}

void bear::ecs::Entity::removeComponent(component_types a_Type)
{
	m_ComponentsToRemove.push_back(a_Type);
}

bear::ecs::TransformComponent* bear::ecs::Entity::transform()
{
	return static_cast<TransformComponent*>(m_ComponentList[component_types::TRANSFORM_COMPONENT]);
}

std::string bear::ecs::Entity::getID()
{
	return m_ID;
}

void bear::ecs::Entity::setID(std::string a_ID)
{
	m_ID = a_ID;
}