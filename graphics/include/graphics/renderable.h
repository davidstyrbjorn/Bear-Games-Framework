#pragma once

#include<core\vector2.h>
#include<core\color.h>

#include"types.h"

namespace bear { namespace graphics { 

	class Shader;

	class Renderable {
	private:
		/* Shared renderable members */
		core::Vector2f m_Position;
		core::Vector2f m_Size;
		core::Color m_Color;
		const renderable_type m_Type;

		/* These values are used if we're dirty rendering! */
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_IBO;

	public:
		/* Constructor(s) */
		Renderable(renderable_type a_T);
		Renderable(renderable_type a_T, core::Vector2f a_P, core::Vector2f a_S, core::Color a_C);

		/* 
		*** Shared renderable methods ***
		*/
		/*
		( VIRTUAL )
		* Method used for dirty rendering (rendering with single drawcalls without a centralized renderer) 
		* Use case: games with limited rendering target ( < 100 )
		*/
		virtual void draw(Shader &a_Shader);

		/*
		( NON-VIRTUAL )
		* Getters & Setters
		*/
		void setPosition(core::Vector2f &a_P);
		void setColor(core::Color &a_C);
		const core::Vector2f getPosition();
		const core::Color getColor();

	private:
		/*
		( NON_VIRTUAL )
		* Gets called if dirty rendering is enabled by the user
		* Does OpenGL calls and sets up the renderable shape for OpenGL render calls through Renderable::draw()
		*/
		void setupBuffers();
	};

}} 