#pragma once

#include"transform.h"
#include"../core/color.h"

#include"types.h"

namespace bear { namespace graphics { 

	struct Image;

	class Renderable {
	protected:
		/* Shared renderable members */
		Transform m_Transform;
		core::Color m_Color;
		renderable_type m_Type;

	public:
		std::string m_TextureName;

	public:
		/* Constructor(s) */
		Renderable() : m_Type(renderable_type::Triangle), m_Color(core::Color::White()) { } // default constructor 
		Renderable(renderable_type a_T) : m_Type(a_T), m_Color(core::Color::White()) { } 
		Renderable(const std::string& a_TextureName); // Sprite constructor 

		/* Destructor */
		virtual ~Renderable();

		/* Getters & Setters */
		void setColor(core::Color &a_C);
		const core::Color getColor();
		Transform& transform();
		const renderable_type getType();
		void setType(renderable_type a_Type);
	};

}} 