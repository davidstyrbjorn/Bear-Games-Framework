#pragma once

#include"../component.h"

#include<core\vector2.h>

namespace bear { namespace ecs { 

	class TransformComponent : public Component
	{
	public:
		core::Vector2f m_Position;
		core::Vector2f m_Size;

	public:
		TransformComponent();
		TransformComponent(const core::Vector2f a_Position);
		TransformComponent(const core::Vector2f a_Position, const core::Vector2f a_Size);

		bool reset() override;
		int getType() { return component_types::TRANSFORM_COMPONENT; }
	};

} } 