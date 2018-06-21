#include"../include/graphics/renderable.h"

#define GLEW_STATIC
#include"GL\glew.h"

void bear::graphics::Renderable::draw(Shader & a_Shader)
{
	if (dirtyRender) {
		printf("x");
		// Dirty render is enabled!
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(0.5, 0);
		glVertex2f(0.5, 0.5);
		glEnd();
	}
	else {
		// No dirty render
	}
}

void bear::graphics::Renderable::setPosition(core::Vector2f & a_P)
{
	m_Position = a_P;
}

void bear::graphics::Renderable::setColor(core::Color & a_C)
{
	m_Color = a_C;
}

const bear::core::Vector2f bear::graphics::Renderable::getPosition()
{
	return m_Position;
}

const bear::core::Color bear::graphics::Renderable::getColor()
{
	return m_Color;
}