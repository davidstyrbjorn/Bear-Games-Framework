#pragma once

#include"../component.h"

#include<core\color.h>

namespace bear { namespace ecs { 

	class RectangleComponent : public Component {
	public:
		RectangleComponent();

		void init() override { }
		int getType() override { return component_types::RECTANGLE_COMPONENT; }
	};

} } 