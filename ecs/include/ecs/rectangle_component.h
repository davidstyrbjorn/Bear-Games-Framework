#pragma once

#include"component.h"

#include"renderable_base.h"

namespace bear { namespace ecs { 

	class RectangleComponent : public RenderableBase, public Component {
	public:
		RectangleComponent(core::Color a_Color);

		void init() override { }
		component_types getType() override { return component_types::RENDERABLE_COMPONENT; }
	};

} } 