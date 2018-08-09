#include"../include/graphics/renderers/batch_renderer.h"

#define GLEW_STATIC
#include<GL\glew.h>

#include"../include/graphics/shader.h"
#include"../include/graphics/renderable.h"
#include"../include/graphics/view.h"
#include"../include/graphics/graphics.h"
#include<core\matrix4x4.h>

#include<vector>
#include<assert.h>
#include<stdlib.h>

using namespace bear::graphics;

View& BatchRenderer::defaultView = View();

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
	Graphics::s_DefaultShader->enable();
	Graphics::s_DefaultShader->setUniformInteger("texture_sampler", 0);

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

	// <===============================================	  ===================================================   ================================================>
	// <===============================================	  ===================================================   ================================================>

	glGenBuffers(1, &_textured_buffers.VBO);
	glGenBuffers(1, &_textured_buffers.IBO);
	glGenVertexArrays(1, &_textured_buffers.VAO);

	glBindVertexArray(_textured_buffers.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), nullptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1); // color		
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(core::Vector2f));
	glEnableVertexAttribArray(2); // uv							   
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(core::Vector2f) + sizeof(core::Color)));

	glActiveTexture(GL_TEXTURE0);

	unsigned int indicies[] = { 0, 1, 2, 0, 2, 3 };
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _textured_buffers.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

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

void bear::graphics::BatchRenderer::flush(View& a_View)
{
	// Unlit flush
	Graphics::s_DefaultShader->enable();
	Graphics::s_DefaultShader->setUniformMatrix4x4("view_matrix", a_View.getViewMatrix());
	Graphics::s_DefaultShader->setUniformInteger("texture_mode", 0);

	glBindVertexArray(_unlit_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _unlit_buffers.VBO);
	glDrawArrays(GL_TRIANGLES, 0, m_UnlitVertCount);

	// Texture flush
	Graphics::s_DefaultShader->setUniformInteger("texture_mode", 1);
	glBindVertexArray(_textured_buffers.VAO);
	while (!_textured_buffers.m_TextureBatch.empty()) 
	{
		graphics::Renderable* renderable = _textured_buffers.m_TextureBatch.back();
		core::Vector2f pos = renderable->transform().m_Position;
		core::Vector2f size = renderable->transform().m_Size;
		core::Color col = renderable->getColor();

		// Bind
		glBindTexture(GL_TEXTURE_2D, renderable->getTextureID());
		glBindBuffer(GL_ARRAY_BUFFER, _textured_buffers.VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _textured_buffers.IBO);

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

	Graphics::s_DefaultShader->disable();
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
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