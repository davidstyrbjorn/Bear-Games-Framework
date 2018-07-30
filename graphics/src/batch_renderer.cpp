#include"../include/graphics/renderers/batch_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/renderable.h"
#include"../include/graphics/graphics.h"
#include<core\matrix4x4.h>

#include<vector>
#include<assert.h>
#include<stdlib.h>

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

	m_TextureShader = new Shader();
	m_TextureShader->compile("D:\\temp\\vert.txt", "D:\\temp\\frag_texture.txt", true);
	m_TextureShader->enable();
	m_TextureShader->setUniformMatrix4x4("projection_matrix", core::Matrix4x4::Orthographic(0, a_Width, a_Height, 0, -1, 1));

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

	glGenBuffers(1, &_textured_buffers.VBO);
	glGenVertexArrays(1, &_textured_buffers.VAO);

	glBindVertexArray(_textured_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), nullptr, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // position

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
	else {
		submit_texture(a_Renderable);
	}
}

void bear::graphics::BatchRenderer::flush()
{
	// Unlit flush
	m_UnlitShader->enable();
	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glDrawArrays(GL_TRIANGLES, 0, m_UnlitVertCount);

	// Texture flush
	m_TextureShader->enable();
	glBindVertexArray(_textured_buffers.VAO);
	while (!_textured_buffers.m_TextureBatch.empty()) 
	{
		graphics::Renderable* renderable = _textured_buffers.m_TextureBatch.back();
		graphics::Image* image = renderable->getImage();
		core::Vector2f pos = renderable->transform().m_Position;
		core::Vector2f size = renderable->transform().m_Size;
		core::Color col = renderable->getColor();

		// Bind
		glBindTexture(GL_TEXTURE_2D, _textured_buffers.TBO);
		glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _textured_buffers.IBO);

		// Update texture data with provided image
		glTexImage2D(_textured_buffers.TBO, 0, image->m_Format, image->m_ImageSize.x, image->m_ImageSize.y, 0, image->m_Format, GL_UNSIGNED_BYTE, image->m_ImageData);
		// Update texture vertex buffer data with renderable data
		Vertex vertData[] = {
			{ pos, col, core::Vector2f(0, 0) },
			{ core::Vector2f(pos.x, pos.y + size.y), col, core::Vector2f(0, 1.0f) },
			{ pos+size, col, core::Vector2f(1.0f, 1.0f) },
			{ core::Vector2f(pos.x + size.x, pos.y), col, core::Vector2f(1.0f, 0) }
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		_textured_buffers.m_TextureBatch.pop_back();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

Shader & bear::graphics::BatchRenderer::getUnlitShader()
{
	return *m_UnlitShader;
}

Shader & bear::graphics::BatchRenderer::getTextureShader()
{
	return *m_TextureShader;
}

void bear::graphics::BatchRenderer::submit_unlit(Renderable & a_UnlitRenderable)
{
	size_t _offset = m_UnlitVertCount * sizeof(Vertex);
	// Overshot buffer size, this is bad and stuff won't get rendered
	assert(_offset < UNLIT_BUFFER_SIZE);

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
	glBufferSubData(GL_ARRAY_BUFFER, _offset, sizeof(Vertex)*vertList.size(), &vertList[0]);

	if (a_UnlitRenderable.getType() == renderable_type::Rectangle) {
		m_UnlitVertCount += 6;
	}
	else {
		m_UnlitVertCount += 3;
	}
}

void bear::graphics::BatchRenderer::submit_texture(Renderable & a_TexturedRenderable)
{
	_textured_buffers.m_TextureBatch.push_back(&a_TexturedRenderable);
}