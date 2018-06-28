#include"../include/graphics/renderable.h"

#include"../include/graphics/graphics.h"
#include"../include/graphics/vertex.h"

#include<core\vector2.h>
#include<core\matrix4x4.h>

#include<vector>

#define GLEW_STATIC
#include"GL\glew.h"

bear::graphics::Renderable::Renderable(renderable_type a_T) : m_Type(a_T), m_Position(), m_Size(), m_Color()
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		this->setupBuffers();
	}
}

bear::graphics::Renderable::Renderable(renderable_type a_T, core::Vector2f a_P, core::Vector2f a_S, core::Color a_C) :
	m_Type(a_T), 
	m_Position(a_P),
	m_Size(a_S),
	m_Color(a_C) 
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		this->setupBuffers();
	}
}

void bear::graphics::Renderable::draw(Shader & a_Shader)
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		// Do OpenGL stuff
		a_Shader.setUniformMatrix4x4("model_matrix", core::Matrix4x4::Translation(core::Vector3f(m_Position.x, m_Position.y, 0)));

		glBindVertexArray(m_VAO);
		if (m_Type == graphics::renderable_type::Triangle)
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		else
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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

void bear::graphics::Renderable::setupBuffers()
{
	/* 
	1. Create VBO and fill with data
	2. Create IBO and fill with data
	2. Create and bind VAO
	3. Bind VBO to VAO and setup the vertex attrib layout
	4. Bind IBO to VAO
	5. Unbind and be done
	*/

	// Data
	std::vector<Vertex> vertexData;
	std::vector<GLuint> indexData;
	if (m_Type == graphics::renderable_type::Triangle) {
		// VBO data 
		vertexData.push_back({ core::Vector2f(0.0f, 0.0f), m_Color });
		vertexData.push_back({ core::Vector2f(0.0f, m_Size.y), m_Color });
		vertexData.push_back({ core::Vector2f(m_Size), m_Color });
		// IBO data
		indexData = { 0, 1, 2 };
	}
	else if (m_Type == graphics::renderable_type::Rectangle) {
		// VBO data 
		vertexData.push_back({ core::Vector2f(0.0f, 0.0f), m_Color });
		vertexData.push_back({ core::Vector2f(0.0f, m_Size.y), m_Color });
		vertexData.push_back({ core::Vector2f(m_Size), m_Color });
		vertexData.push_back({ core::Vector2f(m_Size.x, 0.0f), m_Color });
		// IBO data
		indexData = { 0, 1, 2, 2, 3, 0 };
	}

	// VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), &vertexData[0], GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// VertexAttribPointer with our m_VBO bound
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f)));

	// IBO 
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), &indexData[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
