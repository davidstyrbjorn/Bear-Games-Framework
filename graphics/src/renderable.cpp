#include"../include/graphics/renderable.h"

#include"../include/graphics/graphics.h"
#include"../include/graphics/vertex.h"

#include<core\vector2.h>
#include<core\matrix4x4.h>

#include<vector>

#define GLEW_STATIC
#include"GL\glew.h"

bear::graphics::Renderable::Renderable(renderable_type a_T, core::Vector2f a_P, std::string a_ImagePath) : m_Type(a_T), m_Position(a_P), m_Size(), m_Color()
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		this->setupBuffers(a_ImagePath);
	}
}

bear::graphics::Renderable::Renderable(renderable_type a_T, core::Vector2f a_P, core::Vector2f a_S, core::Color a_C) :
	m_Type(a_T), 
	m_Position(a_P),
	m_Size(a_S),
	m_Color(a_C) 
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		this->setupBuffers("");
	}
}

bear::graphics::Renderable::~Renderable()
{
	if (bear::graphics::Graphics::doDirtyRender()) {
		// Remove buffers & vertex array objects
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_IBO);
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
		else {
			if (m_Type == graphics::renderable_type::Sprite)
				glBindTexture(GL_TEXTURE_2D, m_TBO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
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

void bear::graphics::Renderable::setupBuffers(std::string a_ImagePath)
{
	/* 
	1. Create VBO and fill with data
	2. Create IBO and fill with data
	2. Create and bind VAO
	3. Bind VBO to VAO and setup the vertex attrib layout
	4. Bind IBO to VAO
	5. Unbind and be done
	*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Data
	std::vector<Vertex> vertexData;
	std::vector<GLuint> indexData;
	if (m_Type == graphics::renderable_type::Triangle) {
		// VBO data 
		vertexData.push_back({ core::Vector2f(0.0f, 0.0f), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(0.0f, m_Size.y), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(m_Size), m_Color, core::Vector2f(0.0f, 0.0f) });
		// IBO data
		indexData = { 0, 1, 2 };
	}
	else if (m_Type == graphics::renderable_type::Rectangle) {
		// VBO data 
		vertexData.push_back({ core::Vector2f(0.0f, 0.0f), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(0.0f, m_Size.y), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(m_Size), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(m_Size.x, 0.0f), m_Color, core::Vector2f(0.0f, 0.0f) });
		// IBO data
		indexData = { 0, 1, 2, 2, 3, 0 };
	}
	else if (m_Type == graphics::renderable_type::Circle) {

	}
	else if (m_Type == graphics::renderable_type::Sprite) {
		// VBO data 

		Image image(a_ImagePath);
		m_Size = core::Vector2f((int)(image.m_ImageSize.x), (int)(image.m_ImageSize.y));

		vertexData.push_back({ core::Vector2f(0.0f, 0.0f), m_Color, core::Vector2f(0.0f, 0.0f) });
		vertexData.push_back({ core::Vector2f(0.0f, m_Size.y), m_Color, core::Vector2f(0.0f, 1.0f) });
		vertexData.push_back({ core::Vector2f(m_Size), m_Color, core::Vector2f(1.0f, 1.0f) });
		vertexData.push_back({ core::Vector2f(m_Size.x, 0.0f), m_Color, core::Vector2f(1.0f, 0.0f) });
		// IBO data
		indexData = { 0, 1, 2, 2, 3, 0 };
		// TBO Creation
		glActiveTexture(GL_TEXTURE0);

		glGenTextures(1, &m_TBO);
		glBindTexture(GL_TEXTURE_2D, m_TBO);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.m_ImageSize.x, image.m_ImageSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image.m_ImageData);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
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
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)));

	// IBO 
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), &indexData[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}
