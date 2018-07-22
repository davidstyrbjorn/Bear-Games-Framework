#pragma once

#include<core\vector2.h>
#include<core\color.h>

#include"types.h"

namespace bear { namespace graphics { 

	class Renderable {
	protected:
		/* Shared renderable members */
		core::Vector2f m_Position;
		core::Vector2f m_Size;
		core::Color m_Color;
		const renderable_type m_Type;

	public:
		/* Constructor(s) */
		Renderable(renderable_type a_T) : m_Type(a_T) { }

		/* Destructor */
		virtual ~Renderable() { }

		/* Getters & Setters */
		void setPosition(core::Vector2f &a_P);
		void setColor(core::Color &a_C);
		const core::Vector2f getPosition();
		const core::Color getColor();
	};

}} 