#pragma once

#include"renderable.h"

namespace bear { namespace graphics { 

	class Shader;

	class Shape : public Renderable {
	public:
		static Shape CreateTriangle(core::Vector2f a_Position, core::Vector2f a_Size, core::Color a_Color);
		static Shape CreateRectangle(core::Vector2f a_Position, core::Vector2f a_Size, core::Color a_Color);
		static Shape CreateSprite(core::Vector2f a_Position, std::string a_ImagePath);

	public:
		Shape(renderable_type a_Type);
		~Shape();

		void draw(Shader &a_Shader);
		void setupBuffers(std::string a_ImagePath);

	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_IBO;
		unsigned int m_TBO;
	};

} }