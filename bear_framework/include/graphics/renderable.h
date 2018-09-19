#pragma once

#include"transform.h"
#include"../core/color.h"

#include"types.h"

namespace bear { namespace graphics { 

	struct Image;
	class Texture;

	class Renderable {
	protected:
		/* Shared renderable members */
		Transform m_Transform;
		core::Color m_Color;
		renderable_type m_Type;

	private:
		Texture* m_Texture;

	public:
		/* Constructor(s) */
		Renderable() : m_Type(renderable_type::Triangle), m_Color(core::Color::White()) { } // default constructor 
		Renderable(renderable_type a_T) : m_Type(a_T), m_Color(core::Color::White()) { } 
		Renderable(Image& a_Image); // Sprite constructor 

		/* Destructor */
		virtual ~Renderable();

		/* Getters & Setters */
		void setColor(core::Color &a_C);
		const core::Color getColor();
		Transform& transform();
		const renderable_type getType();
		void setType(renderable_type a_Type);

		int getTextureID();
		void setTextureImage(const Image& a_Image);

	};

}} 