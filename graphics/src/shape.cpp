#include"../include/graphics/shape.h"

#include"../include/graphics/graphics.h"
#include<core\matrix4x4.h>
#include<vector>

#define GLEW_STATIC
#include<GL\glew.h>

bear::graphics::Shape::Shape(renderable_type a_Type) : Renderable(a_Type)
{
}

bear::graphics::Shape::~Shape()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteTextures(1, &m_TBO);
}

bear::graphics::Shape bear::graphics::Shape::CreateTriangle(core::Vector2f a_Position, core::Vector2f a_Size, core::Color a_Color)
{
	Shape shape(renderable_type::Triangle);
	shape.m_Position = a_Position;
	shape.m_Size = a_Size;
	shape.m_Color = a_Color;
	shape.setupBuffers("");
	return shape;
}

bear::graphics::Shape bear::graphics::Shape::CreateRectangle(core::Vector2f a_Position, core::Vector2f a_Size, core::Color a_Color)
{
	Shape shape(renderable_type::Rectangle);
	shape.m_Position = a_Position;
	shape.m_Size = a_Size;
	shape.m_Color = a_Color;
	shape.setupBuffers("");
	return shape;
}

bear::graphics::Shape bear::graphics::Shape::CreateSprite(core::Vector2f a_Position, std::string a_ImagePath)
{
	Shape shape(renderable_type::Sprite);
	shape.m_Position = a_Position;
	shape.setupBuffers(a_ImagePath);
	return shape;
}

void bear::graphics::Shape::draw(Shader & a_Shader)
{
	// Do OpenGL stuff
	a_Shader.setUniformMatrix4x4("model_matrix", core::Matrix4x4::Translation(core::Vector3f(m_Position.x, m_Position.y, 0)));

	glBindVertexArray(m_VAO);
	// Triangle
	if (m_Type == graphics::renderable_type::Triangle) 
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}
	else // Rectangle/Sprite 
	{
		if (m_Type == graphics::renderable_type::Sprite)
		{
			glBindTexture(GL_TEXTURE_2D, m_TBO);
		}

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void bear::graphics::Shape::setupBuffers(std::string a_ImagePath)
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
