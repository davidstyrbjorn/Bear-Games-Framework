#pragma once

#include"transform.h"
#include<core\color.h>

#include"types.h"

namespace bear { namespace graphics { 

	class Renderable {
	protected:
		/* Shared renderable members */
		Transform m_Transform;
		core::Color m_Color;
		const renderable_type m_Type;

	public:
		/* Constructor(s) */
		Renderable(renderable_type a_T) : m_Type(a_T) { }

		/* Destructor */
		virtual ~Renderable() { }

		/* Getters & Setters */
		void setColor(core::Color &a_C);
		const core::Color getColor();
		Transform& transform();
	};

}} 