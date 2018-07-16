#pragma once

#include"ecs.h"

namespace bear { namespace ecs { 

	class Component {
	public:
		virtual void init() = 0;
		virtual component_types getType() = 0;
	};

} } 