#include"../include/ecs/bear_components/transform_component.h"

bear::ecs::TransformComponent::TransformComponent() : 
	m_Position(), m_Size()
{

}

bear::ecs::TransformComponent::TransformComponent(const core::Vector2f a_Position) : 
	m_Position(a_Position), m_Size()
{

}

bear::ecs::TransformComponent::TransformComponent(const core::Vector2f a_Position, const core::Vector2f a_Size) :
	m_Position(a_Position), m_Size(a_Size)
{
}

bool bear::ecs::TransformComponent::reset()
{
	m_Position = core::Vector2f();
	m_Size = core::Vector2f();

	return true;
}