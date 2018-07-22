#pragma once

#include"../component.h"

#include<core\color.h>

namespace bear { namespace ecs {

		class SpriteComponent : public Component {
		public:
			SpriteComponent();

			void init() override { }
			int getType() override { return component_types::SPRITE_COMPONENT; }
		};

	
} }