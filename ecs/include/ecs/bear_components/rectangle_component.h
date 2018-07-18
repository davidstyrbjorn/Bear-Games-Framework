#pragma once

#include"../component.h"

#include"../renderable_base.h"

namespace bear { namespace ecs { 

	class RectangleComponent : public RenderableBase, public Component {
	public:
		RectangleComponent(core::Color a_Color);

		void init() override { }
		int getType() override { return 10; }
	};

} } 