#include"../include/graphics/renderers/batch_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/renderable.h"
#include"../include/graphics/graphics.h"
#include<core\matrix4x4.h>

#include<vector>

using namespace bear::graphics;

bear::graphics::BatchRenderer::BatchRenderer()
{
	// Do nothing
}

bear::graphics::BatchRenderer::~BatchRenderer()
{
	//  @ Delete stuff
}

void bear::graphics::BatchRenderer::init(unsigned int a_Width, unsigned int a_Height)
{
	// Initalize objects and buffers
	m_UnlitShader = new Shader();
	m_UnlitShader->compile("D:\\temp\\vert.txt", "D:\\temp\\frag_unlit.txt", true);
	m_UnlitShader->enable();
	m_UnlitShader->setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, a_Width, a_Height, 0, -1, 1));

	glGenBuffers(1, &_unlit_buffers.VBO);
	glGenVertexArrays(1, &_unlit_buffers.VAO);

	// Setup the vertex attrib layouts
	glBindVertexArray(_unlit_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, UNLIT_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); // color 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(core::Vector2f));
	glEnableVertexAttribArray(2); // uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)));

	glBindVertexArray(0);
}

void bear::graphics::BatchRenderer::begin()
{
	m_UnlitVertCount = 0; 

	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, UNLIT_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW); // reset buffer data
}

void bear::graphics::BatchRenderer::submit(Renderable & a_Renderable)
{
	if (a_Renderable.getType() != renderable_type::Sprite) {
		submit_unlit(a_Renderable);
	}
}

void bear::graphics::BatchRenderer::flush()
{
	m_UnlitShader->enable();
	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);

	glDrawArrays(GL_TRIANGLES, 0, m_UnlitVertCount);

	//m_UnlitShader->disable();
	glBindVertexArray(0);
}

void bear::graphics::BatchRenderer::submit_unlit(Renderable & a_UnlitRenderable)
{
	// @ Control we're not overshooting buffer size
	// @ This code only works for triangles 

	core::Vector2f pos = a_UnlitRenderable.transform().m_Position;
	core::Vector2f size = a_UnlitRenderable.transform().m_Size;
	core::Color col = a_UnlitRenderable.getColor();
	core::Vector2f uv = core::Vector2f(0, 0);

	std::vector<Vertex> vertList;
	if (a_UnlitRenderable.getType() == renderable_type::Triangle) {
		vertList.push_back({ pos, col,  uv });
		vertList.push_back({ core::Vector2f(pos.x, pos.y + size.y), col, uv });
		vertList.push_back({ pos + size, col, uv });
	}
	else {
		// No indices so we're doing 2 triangles
		vertList.push_back({ pos, col,  uv });
		vertList.push_back({ core::Vector2f(pos.x, pos.y + size.y), col, uv });
		vertList.push_back({ pos + size, col, uv });

		vertList.push_back({ pos, col, uv });
		vertList.push_back({ core::Vector2f(pos.x + size.x, pos.y), col, uv });
		vertList.push_back({ pos + size, col, uv });
	}

	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glBufferSubData(GL_ARRAY_BUFFER, (m_UnlitVertCount)*(sizeof(Vertex)), sizeof(Vertex)*vertList.size(), &vertList[0]);

	m_UnlitVertCount += 6;
}

void bear::graphics::BatchRenderer::submit_texture(Renderable & a_TexturedRenderable)
{

}