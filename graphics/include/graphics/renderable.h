#pragma once

#include<core\vector2.h>
#include<core\color.h>

namespace bear { namespace graphics { 

	class Shader;

	class Renderable {
	private:
		/* Shared renderable members */
		core::Vector2f m_Position;
		core::Color m_Color;

	public:
		/* Constructor(s) */
		Renderable() : m_Position(), m_Color() { }
		Renderable(core::Vector2f a_P, core::Color a_C) : m_Position(a_P), m_Color(a_C) { }

		/* Shared renderable methods */

		/*
		( VIRTUAL )
		* Method used for dirty rendering (rendering with single drawcalls without a centralized renderer) 
		* Use case: games with limited rendering target ( < 100 )
		*/
		virtual void draw(Shader &a_Shader) = 0;

		/*
		( NON-VIRTUAL )
		* Getters & Setters
		*/
		void setPosition(core::Vector2f &a_P);
		void setColor(core::Color &a_C);
		const core::Vector2f getPosition();
		const core::Color getColor();
	};

}} 