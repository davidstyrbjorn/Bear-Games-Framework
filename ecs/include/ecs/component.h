#pragma once

#include"ecs.h"

namespace bear { namespace ecs { 

	class Component {
	public:
		virtual void init() { }
		virtual component_types getType() { return static_cast<component_types>(-1); }
		virtual void reset() { }
	};

} } 