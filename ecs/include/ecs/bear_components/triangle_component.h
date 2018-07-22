#pragma once

#include"../component.h"

#include<core\color.h>

namespace bear { namespace ecs {

		class TriangleComponent : public Component {
		public:
			TriangleComponent();

			void init() override { }
			int getType() override { return component_types::TRIANGLE_COMPONENT; }
		};

	
} }