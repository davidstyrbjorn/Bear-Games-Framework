#pragma once

#include<core\vector2.h>
#include<core\color.h>

namespace bear { namespace ecs {

	class RenderableBase {
	protected:
		core::Color m_Color;

	public:
		// Sets the color
		void setColor(const core::Color a_C) { m_Color = a_C; }

		// Return the color
		core::Color getColor() { return m_Color; }
	};

} }